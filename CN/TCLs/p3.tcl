# --- Simulation Setup ---
set ns [new Simulator]
set stop_time 5.0

# Trace Files
set tf [open p3ping.tr w]
set nf [open p3ping.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Termination Procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam p3ping.nam &
    exit 0
}

# --- Topology Setup ---

# Create Nodes
set n0 [$ns node] ; # Ping Source 0
set n1 [$ns node] ; # Unused
set n2 [$ns node] ; # Router (Central)
set n3 [$ns node] ; # Unused
set n4 [$ns node] ; # Ping Destination 4
set n5 [$ns node] ; # Ping Source 5
set n6 [$ns node] ; # Ping Destination 6

# Node Labels and Colors
$ns color 1 "red"
$ns color 2 "blue"
$n0 label "Ping0"
$n2 label "Router"
$n4 label "Ping4"
$n5 label "Ping5"
$n6 label "Ping6"

# Links and Queues
# Link n0 <-> n2: 100Mb/s, 300ms, DropTail, Q-limit 5
$ns duplex-link $n0 $n2 100Mb 300ms DropTail
$ns queue-limit $n0 $n2 5

# Link n5 <-> n2: 100Mb/s, 300ms, DropTail, Q-limit 5
$ns duplex-link $n5 $n2 100Mb 300ms DropTail
$ns queue-limit $n5 $n2 5

# Link n2 <-> n4: 1Mb/s, 300ms, DropTail, Q-limit 3 (Bottleneck to n4)
$ns duplex-link $n2 $n4 1Mb 300ms DropTail
$ns queue-limit $n2 $n4 3

# Link n2 <-> n6: 1Mb/s, 300ms, DropTail, Q-limit 2 (Bottleneck to n6)
$ns duplex-link $n2 $n6 1Mb 300ms DropTail
$ns queue-limit $n2 $n6 2

# Unused links (n1, n3) defined for completeness of topology:
$ns duplex-link $n1 $n2 1Mb 300ms DropTail
$ns duplex-link $n3 $n2 1Mb 300ms DropTail

# --- Agent Creation and Custom RTT Handler ---

# Define the custom Ping RTT reception procedure
Agent/Ping instproc recv {from rtt} {
    $self instvar node_
    puts "Node [$node_ id] received reply from $from with RTT: $rtt"
}

# Ping Flow 0 (n0 -> n4)
set ping0 [new Agent/Ping]
$ns attach-agent $n0 $ping0
$ns connect $ping0 $n4
$ping0 set class_ 1
$ping0 set packetSize_ 50000 ; # Note: Extremely large size
$ping0 set interval_ 0.0001

# Ping Flow 5 (n5 -> n6)
set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5
$ns connect $ping5 $n6
$ping5 set class_ 2
$ping5 set packetSize_ 50000 ; # Note: Extremely large size
$ping5 set interval_ 0.0001

# --- Scheduling ---

# Use a loop to schedule the repetitive 'send' commands for both pings
for {set t 0.1} {$t < 2.0} {set t [expr $t + 0.1]} {
    $ns at $t "$ping0 send"
    $ns at $t "$ping5 send"
}

$ns at $stop_time "finish"

# Start Simulation
$ns run
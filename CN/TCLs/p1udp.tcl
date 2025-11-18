# Initialization
set ns [new Simulator]

# Files
set tf [open lab1.tr w]
set nf [open lab1.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Termination Procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab1.nam &
    exit 0
}

# --- Topology Setup ---

# Create Nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

# Node Labels
$n0 label "Source/udp0"
$n1 label "Source/udp1"
$n2 label "destination"

# Link Definition and Queue Limit
# Link n0 <-> n2: 10kbps, 100ms delay, DropTail, Q-limit 5
$ns duplex-link $n0 $n2 10kb 100ms DropTail
$ns set queue-limit $n0 $n2 5

# Link n1 <-> n2: 10kbps, 10ms delay, DropTail, Q-limit 5
$ns duplex-link $n1 $n2 10kb 10ms DropTail
$ns set queue-limit $n1 $n2 5

# --- Agents and Applications ---

# Destination Agent (Null)
set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

# Flow 0 (UDP/CBR)
set udp0 [new Agent/UDP]
set cbr0 [new Application/Traffic/CBR]
$ns attach-agent $n0 $udp0
$cbr0 attach-agent $udp0
$ns connect $udp0 $null0
$ns color 1 "red"
$udp0 set class_ 1

# Flow 1 (UDP/CBR)
set udp1 [new Agent/UDP]
set cbr1 [new Application/Traffic/CBR]
$ns attach-agent $n1 $udp1
$cbr1 attach-agent $udp1
$ns connect $udp1 $null0
$ns color 2 "blue"
$udp1 set class_ 2

# Common CBR Parameters
# Note: packetSize_ 500Mb is extremely large for a 10kbps link and might crash the sim.
# It is recommended to use a small size like 500 bytes (500b). I've kept your value.
$cbr0 set packetSize_ 500Mb
$cbr1 set packetSize_ 500Mb
$cbr0 set interval_ 0.01
$cbr1 set interval_ 0.01

# --- Scheduling ---
$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$cbr1 start"
$ns at 9.5 "$cbr0 stop"
$ns at 10.0 "$cbr1 stop"
$ns at 10.0 "finish"

# Start Simulation
$ns run
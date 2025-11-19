# --- Simulation Setup ---
set val(stop) 6.0; # Simulation duration (seconds)
set ns [new Simulator]

# Trace Files
set tracefile [open 1.tr w]
set namfile [open 1.nam w]
$ns trace-all $tracefile
$ns namtrace-all $namfile

# Termination Procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam 1.nam &
    exit 0
}

# --- Topology Setup ---

# Create Nodes
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Links and Queues
# Link n1 <-> n2: 1000Kbps, 60ms delay, DropTail, Q-limit 14
$ns duplex-link $n1 $n2 1000Kb 60ms DropTail
$ns queue-limit $n1 $n2 14

# Link n2 <-> n3: 500Kbps, 60ms delay, DropTail, Q-limit 4
$ns duplex-link $n2 $n3 500Kb 60ms DropTail
$ns queue-limit $n2 $n3 4

# --- Agents and Applications ---

# TCP Sender (Source)
set tcp0 [new Agent/TCP]
$ns attach-agent $n1 $tcp0
$tcp0 set packetSize_ 1500

# TCP Sink (Destination)
set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1

# Connect Agents
$ns connect $tcp0 $sink1

# FTP Application
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

# --- Scheduling ---
$ns at 0.2 "$ftp0 start"
$ns at 5.0 "$ftp0 stop"
$ns at $val(stop) "finish"

# Start Simulation
$ns run
# --- Simulation Setup ---
set ns [new Simulator]

# Trace Files
set tf [open p2.tr w]
set nf [open p2.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Termination Procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam p2.nam &
    exit 0
}

# --- Topology Setup ---

# Create Nodes
set n0 [$ns node] ; # TCP Source
set n1 [$ns node] ; # UDP Source
set n2 [$ns node] ; # Router (Bottleneck)
set n3 [$ns node] ; # Destination

# Node Labels and Colors
$ns color 1 "red"
$ns color 2 "blue"
$n0 label "Source/TCP"
$n1 label "Source/UDP"
$n2 label "Router"
$n3 label "Destination"

# Links (100Mb/s, 1ms delay, DropTail)
$ns duplex-link $n0 $n2 100Mb 1ms DropTail
$ns duplex-link $n1 $n2 100Mb 1ms DropTail
$ns duplex-link $n2 $n3 100Mb 1ms DropTail

# --- Flow 0: TCP (FTP) ---
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$tcp0 set class_ 1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set packetSize_ 500Mb
$ftp0 set interval_ 0.01

set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp0 $sink3

# --- Flow 1: UDP (CBR) ---
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
$udp1 set class_ 2

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 500Mb
$cbr1 set interval_ 0.01

set null3 [new Agent/Null]
$ns attach-agent $n3 $null3
$ns connect $udp1 $null3

# --- Scheduling ---
$ns at 0.1 "$cbr1 start"
$ns at 0.2 "$ftp0 start"
$ns at 9.5 "$cbr1 stop"
$ns at 10.0 "finish"

# Start Simulation
$ns run
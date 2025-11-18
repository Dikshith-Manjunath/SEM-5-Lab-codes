# --- Simulation Setup ---
set ns [new Simulator]

# Trace Files
set tf [open p4.tr w]
set nf [open p4.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Termination Procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam p4.nam &
    exit 0
}

# --- Topology Setup ---

# Create 5 Nodes for the LAN
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# Create LAN: 100Mb/s, 10ms delay, using DropTail Queue and 802.3 MAC
$ns make-lan -trace on "$n0 $n1 $n2 $n3 $n4" 100Mb 10ms LL/Queue/DropTail Mac/802_3

# Node Color Definitions for Traffic Types
$ns color 1 "red"   ; # Used for UDP Flow (CBR2)
$ns color 2 "blue"  ; # Used for TCP Flow 0 (FTP0)
$ns color 3 "green" ; # Used for TCP Flow 1 (FTP1)

# --- Flow 0: TCP (FTP0: n0 -> n2) ---
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$tcp0 set class_ 2 ; # Blue color
$tcp0 set interval_ 0.001

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set sink2 [new Agent/TCPSink]
$ns attach-agent $n2 $sink2
$ns connect $tcp0 $sink2

# --- Flow 1: UDP (CBR2: n2 -> n1) ---
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2
$udp2 set class_ 1 ; # Red color
$udp2 set interval_ 0.001

set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2

set null1 [new Agent/Null]
$ns attach-agent $n1 $null1
$ns connect $udp2 $null1

# --- Flow 2: TCP (FTP1: n1 -> n3) ---
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
$tcp1 set class_ 3 ; # Green color
$tcp1 set interval_ 0.01

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp1 $sink3

# --- Scheduling ---
$ns at 0.1 "$cbr2 start"
$ns at 1.2 "$ftp1 start"
$ns at 1.3 "$ftp0 start"
$ns at 9.5 "$cbr2 stop"
$ns at 9.5 "$ftp1 stop"
$ns at 10.0 "finish"

# Start Simulation
$ns run
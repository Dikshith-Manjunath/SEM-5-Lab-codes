# --- Simulation Setup ---
set ns [new Simulator]
set topo_x 700
set topo_y 700
set num_nodes 4
set stop_time 250.0

# Trace Files and Topography
set tf [open p5.tr w]
$ns trace-all $tf

set topo [new Topography]
$topo load_flatgrid $topo_x $topo_y

set nf [open p5.nam w]
$ns namtrace-all-wireless $nf $topo_x $topo_y

# Create God object (Essential for MANETs)
create-god $num_nodes

# Termination Procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam p5.nam &
    exit 0
}

# --- Wireless Node Configuration ---
$ns node-config \
    -adhocRouting DSDV \
    -llType LL \
    -macType Mac/802_11 \
    -ifqType Queue/DropTail \
    -ifqLen 50 \
    -phyType Phy/WirelessPhy \
    -channelType Channel/WirelessChannel \
    -propType Propagation/TwoRayGround \
    -antType Antenna/OmniAntenna \
    -topoInstance $topo \
    -agentTrace ON \
    -routerTrace ON

# --- Node and Initial Position Setup ---
set n0 [$ns node] ; # TCP Source 0
set n1 [$ns node] ; # TCP Sink 0
set n2 [$ns node] ; # TCP Source 1
set n3 [$ns node] ; # TCP Sink 1

# Initial Positions (X, Y, Z=0)
$n0 set X_ 50 ; $n0 set Y_ 50
$n1 set X_ 200; $n1 set Y_ 200
$n2 set X_ 400; $n2 set Y_ 400
$n3 set X_ 600; $n3 set Y_ 600

# Labels
$n0 label "tcp0"
$n1 label "sink1"
$n2 label "tcp1"
$n3 label "sink2"

# Initial movement (setdest to current position with speed)
$ns at 0.1 "$n0 setdest 50 50 15"
$ns at 0.1 "$n1 setdest 200 200 25"
$ns at 0.1 "$n2 setdest 400 400 25"
$ns at 0.1 "$n3 setdest 600 600 25"

# --- Flow 0: TCP/FTP (n0 -> n1) ---
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1

# --- Flow 1: TCP/FTP (n2 -> n3) ---
set tcp1 [new Agent/TCP]
$ns attach-agent $n2 $tcp1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp1 $sink2

# --- Scheduling ---
$ns at 5.0 "$ftp0 start"
$ns at 10.0 "$ftp1 start"

# Node movement (n2 moves)
$ns at 100.0 "$n2 setdest 500 500 25"

# Termination
$ns at $stop_time "finish"
$ns run
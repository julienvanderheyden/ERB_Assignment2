Number of literals: 16
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
86% of the ground temporal actions in this problem are compression-safe
Initial heuristic = 14.000
b (13.000 | 60.000)b (11.000 | 90.001)b (10.000 | 150.001)b (8.000 | 180.001)b (7.000 | 240.001)b (5.000 | 270.001)b (4.000 | 330.001)b (2.000 | 360.001)b (1.000 | 360.002);;;; Solution Found
; States evaluated: 21
; Cost: 420.003
; Time 0.02
0.000: (goto_waypoint robot1 init wp1)  [60.000]
60.001: (detect_marker robot1 wp1)  [30.000]
90.001: (goto_waypoint robot1 wp1 wp2)  [60.000]
150.001: (detect_marker robot1 wp2)  [30.000]
180.001: (goto_waypoint robot1 wp2 wp3)  [60.000]
240.001: (detect_marker robot1 wp3)  [30.000]
270.001: (goto_waypoint robot1 wp3 wp4)  [60.000]
330.001: (detect_marker robot1 wp4)  [30.000]
360.002: (sort smallest)  [0.001]
360.003: (goto_smallest robot1 wp4 smallest)  [60.000]

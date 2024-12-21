(define (problem task)
(:domain turtlebot)
(:objects
    init wp1 wp2 wp3 wp4 - waypoint
    robot1 - robot
    smallest - smallest_marker
)
(:init
    (robot_at robot1 init)


    (visited init)

    (unvisited wp1)
    (unvisited wp2)
    (unvisited wp3)
    (unvisited wp4)


)
(:goal (and
    (robot_on_smallest robot1)
))
)

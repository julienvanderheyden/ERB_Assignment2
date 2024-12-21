(define (domain turtlebot)

    (:requirements :strips :typing :durative-actions :universal-preconditions)

    (:types
        waypoint - object
        robot - object
        smallest_marker - object
    )

    (:predicates
    	(robot_at ?v - robot ?wp - waypoint)
    	(robot_on_smallest ?v - robot)
    	(visited ?wp - waypoint)
    	(unvisited ?wp - waypoint)
    	(known ?s - smallest_marker) 
    )

    ;; Move to any waypoint
    (:durative-action goto_waypoint
        :parameters (?v - robot ?from ?to - waypoint)
        :duration (= ?duration 60)
        :condition (and
        	(at start (robot_at ?v ?from))
        	(at start (unvisited ?to))
        )
        :effect (and
            (at start (not (robot_at ?v ?from)))
            (at end (robot_at ?v ?to))
        )
    )
    
    ;;Move to the smallest marker
    (:durative-action goto_smallest
    	:parameters(?v - robot ?from - waypoint ?to - smallest_marker)
    	:duration (= ?duration 60)
    	:condition (and 
    		(at start (robot_at ?v ?from))
    		(at start (known ?to))
    	)
    	:effect (and 
    		(at start (not (robot_at ?v ?from)))
    		(at end (robot_on_smallest ?v))

    	)
    )

    ;; Detect the marker
    (:durative-action detect_marker
        :parameters (?v - robot ?wp - waypoint)
        :duration (= ?duration 30)
        :condition (over all (robot_at ?v ?wp))
        :effect (and
        	(at end (visited ?wp)) 
        	(at end (not (unvisited ?wp)))
        )
    )
    
    ;; Sort the markers
    (:action sort
    	:parameters(?m - smallest_marker)
    	:precondition (forall (?wp - waypoint) (visited ?wp))
    	:effect (known ?m)
    )
)


(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents )


(:types 	robot region assignment
)

(:predicates
	(robot_in ?v - robot ?r - region) (visited ?r - region ) (ass_in ?a - assignment ?x - region) (on_robot ?a - assignment) (sub_desk ?r - region)
	      
)

(:functions 
	(act-cost) (triggered ?from ?to - region) (dummy)  (ass_on_rob)
)

(:durative-action goto_region
		:parameters (?v - robot ?from ?to - region)
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)))
	        :effect (and (at start (not (robot_in ?v ?from))) (at start (increase (triggered ?from ?to) 1))
		(at end (robot_in ?v ?to)) (at end (assign (triggered ?from ?to) 0)) (at end (visited ?to)) 	
                (at end (increase (act-cost) (dummy))))
)

(:durative-action take_ass
  :parameters (?v - robot ?r - region ?ass - assignment)
  :duration (= ?duration 1)
  :condition (and (at start (ass_in ?ass ?r))
                  (at start (robot_in ?v ?r))
                  (at start (< (ass_on_rob) 2))
            )
  :effect (and (at start (not (ass_in ?ass ?r)))
               (at end (on_robot ?ass))
               (at end (increase (ass_on_rob) 1)))
)

(:durative-action drop_ass
  :parameters (?v - robot ?r - region ?ass ?asss - assignment)
  :duration (= ?duration 1)
  :condition (and (at start (on_robot ?ass))
  				  (at start (on_robot ?asss))
                  (at start (robot_in ?v ?r))				  
				)
  :effect (and (at start (not (on_robot ?ass)))
				(at start (not (on_robot ?asss)))
               (at end (ass_in ?ass ?r))
			   (at end (ass_in ?asss ?r))
               (at end (decrease (ass_on_rob) 2)))
)


)


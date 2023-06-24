(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents )


(:types 	robot region ass
)

(:predicates
	(robot_in ?v - robot ?r - region) (visited ?r - region ) (ass_in ?a - ass ?x - region) (on_robot ?a - ass) (sub_desk ?r - region)
	      
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

(:action take_ass
	:parameters (?v - robot ?r - region ?ass - ass)
	:precondition (and (ass_in ?ass ?r) (robot_in ?v ?r) (< (ass_on_rob) 2) (not (on_robot ?ass)))
	:effect (and (not (ass_in ?ass ?r)) (on_robot ?ass) (increase (ass_on_rob) 1))
)

(:action drop_ass
	:parameters (?v - robot ?r - region ?ass - ass)
	:precondition (and (on_robot ?ass) (robot_in ?v ?r))
	:effect (and (not (on_robot ?ass)) (ass_in ?ass ?r) (decrease (ass_on_rob) 1)) 
)

)


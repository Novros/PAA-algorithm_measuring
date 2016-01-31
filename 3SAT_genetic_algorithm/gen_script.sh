#!/bin/bash

# generator [num_clauses] [num_variables] [variables_in_clause] [instances] [max_weight]

variables_in_clause=3
instances=50
max_weight=100

clauses=25
variables=24

for clauses in {20,25,30,40,50,60,75,80,90,100} # {25,50,75,100}
do
	./../generator/generator $clauses $variables $variables_in_clause $instances $max_weight
done
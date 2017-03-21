#!/bin/bash
#

rm times
for Erro in 0 1 2
do
    for EdgesAndVertices in 100 1000 5000 10000 50000 100000 250000 500000 750000 1000000 2500000 5000000 7500000 10000000 50000000 #valores para o V+E
    do
        let Vertices=$EdgesAndVertices/2
        ./gen_p1 $Vertices 2 $Erro > test$Erro-$EdgesAndVertices
        echo " ------ " >> times
        echo "$Erro-$EdgesAndVertices" >> times
        (time ./a.out < test$Erro-$EdgesAndVertices) 1>/dev/null  2>> times #nome do ficheiro compilado
        rm test$Erro-$EdgesAndVertices
    done
done

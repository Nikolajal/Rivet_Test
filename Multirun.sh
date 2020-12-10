#! /bin/bash

#############################
#                           #
#   Multirun.sh Bash script #
#                           #
#############################

############################# Variables definition

strun=0
nruns=10
njobs=20
nevents=1000
nTotal=1000000000

############################# Script Run

echo "[INFO] Starting MC Generation"

for run in $(seq $strun $(($strun + $nruns - 1))); do
        
    runid=$(printf "%05d" $run)
    seed=$((123456789 + $run * 2))
    while true; do
        bkgjobs=$(jobs | grep aligenmc | wc -l | xargs)
        if [ $bkgjobs -lt $njobs ]; then
            break
        fi
        echo "[INFO] Sleep while waiting for a free job slot"
        sleep 10
    done
    
    echo "[INFO] Starting Analysis run: $runid"
    
    mkfifo /tmp/$USER/fifo_$seed.hepmc
    
    aligenmc -g pythia8 -E 7000 -N $nevents -S $seed -o /tmp/$USER/fifo_$seed.hepmc &> /tmp/$USER/aligenmc_$seed.log
    
    rivet -a ALICE_2021_123Test --pwd /tmp/$USER/fifo_$seed.hepmc -o Rivet_$seed.yoda &> /tmp/$USER/rivet_$seed.log
    
    #&& rm /tmp/$USER/fifo_$seed.hepmc && rm /tmp/$USER/aligenmc_$seed.log && rm /tmp/$USER/rivet_$seed.log

done
exit 0

############################# NOTES

#mkfifo /tmp/$USER/fifo_$UID.hepmc
#aligenmc -g pythia8 -E 7000 -N 10000 -o /tmp/$USER/fifo_$UID.hepmc &> /tmp/$USER/aligenmc_$UID.log &
#rivet -a ALICE_2010_S8625980 /tmp/$USER/fifo_$UID.hepmc
#rm /tmp/$USER/fifo_$UID.hepmc

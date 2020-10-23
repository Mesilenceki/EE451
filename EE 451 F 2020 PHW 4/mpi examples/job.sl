#!/bin/bash
#SBATCH --ntasks-per-node=1
#SBATCH --nodes=4
#SBATCH --time=00:01:00
#SBATCH --output=mpijob.out
#SBATCH --error=mpijob.err
#SBATCH --export=NONE

source /usr/usc/openmpi/default/setup.sh

srun --ntasks=${SLURM_NTASKS} --mpi=pmi2 ./go



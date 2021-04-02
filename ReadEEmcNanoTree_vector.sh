#!/bin/sh

dirname="/gpfs/mnt/gpfs01/star/pwg/ananyapaul/jobOutput/Run15trans/"
basenameIn="RunEEmcNanoDstMaker_"
basenameOut="EEmcNanoTreeQA_"

RunStart=16064077 #subject to change
RunEnd=16064078 #subject to change
RunGap=1

for((r=RunStart;r<=RunEnd;r++)); do
    #rp=$($r)
    filename=$basenameIn`printf "%05d\n" $r`.root
    echo filename $filename
    outname=$basenameOut`printf "%05d\n" $r`.root
    echo outname $outname
    root -b -q ReadEEmcNanoTree_vector.C\(\"$dirname\",\"$filename\",\"$outname\",$RunStart,$RunEnd\)
done


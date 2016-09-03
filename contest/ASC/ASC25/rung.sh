for i in {1..5}; do
  for j in {1..5}; do
    for k in {1..5}; do
      echo "running ${i} ${j} ${k}"
      echo "${i} ${j} ${k}" | ./g >> tmp.in
    done
  done
done

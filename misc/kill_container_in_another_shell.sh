for pid in $(pgrep container); do kill $pid; done

#pgrep xxx aka ps -e|grep xxx|awk '{print $1}'
#需要在另一个shell才能杀掉。因为本身shell内是处理不了自己的
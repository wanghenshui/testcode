package main

import (
	"fmt"
	"time"
)


func main() {
 timeNow := time.Now() //获取当前时间
    //获取当前零时
    zeroHour := time.Date(timeNow.Year(), timeNow.Month(), timeNow.Day(), 0, 0, 0, 0, timeNow.Location())
fmt.Println(timeNow)
fmt.Println(zeroHour)
	fmt.Println(timeNow.Sub(zeroHour))
	diff, _ := time.ParseDuration("20h30m")
	fmt.Println(diff < timeNow.Sub(zeroHour))
    
	fmt.Println(diff)
	dd, _ := time.ParseDuration("1h")
	d := diff +dd
	fmt.Println(d < timeNow.Sub(zeroHour))
	fmt.Println(d)
	empty, err := time.ParseDuration("")
	fmt.Println(empty)
	fmt.Println(err)
}


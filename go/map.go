package main

import (
	"fmt"
)



func main() {
    var countryCapitalMap map[string] *string /*创建集合 */
    countryCapitalMap = make(map[string]*string)

    /* map插入key - value对,各个国家对应的首都 */
	b := "bb"
    countryCapitalMap [ "France" ] = &b
	c :="cc"
    countryCapitalMap [ "Italy" ] = &c

    /*使用键输出地图值 */
    for country := range countryCapitalMap {
        fmt.Println(country, "首都是", countryCapitalMap [country])
    }

    /*查看元素在集合中是否存在 */
    capital, ok := countryCapitalMap [ "American" ] /*如果确定是真实的,则存在,否则不存在 */
    /*fmt.Println(capital) */
    /*fmt.Println(ok) */
    if (ok) {
        fmt.Println("American 的首都是", capital)
    } else {
        fmt.Println("American 的首都不存在")
    }
    var delta map[string] *string /*创建集合 */
    delta = make(map[string]*string)
    delta = countryCapitalMap


    var l map[string] *string /*创建集合 */
    l = make(map[string]*string)

	for k, v := range countryCapitalMap {
		if k != "France" {
			l[k] = v
		}
	}

	fmt.Println( len(delta), len(countryCapitalMap),len(l))
	delete(delta, "Italy")
	fmt.Println( len(delta), len(countryCapitalMap),len(l))
}

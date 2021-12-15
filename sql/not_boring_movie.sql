--https://leetcode-cn.com/problems/not-boring-movies/description/
select distinct cinema.* from cinema 
where cinema.id%2=1 and cinema.description !="boring" 
order by rating desc;
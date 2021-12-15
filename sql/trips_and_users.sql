SELECT Request_at Day, 
ROUND(COUNT(IF(Status != 'completed', TRUE, NULL)) / COUNT(*), 2) 'Cancellation Rate' 
FROM Trips 
WHERE (Request_at between '2013-10-01' and '2013-10-03') 
		and Client_Id IN 
		(SELECT Users_Id FROM Users WHERE Banned = 'No') GROUP BY Request_at;
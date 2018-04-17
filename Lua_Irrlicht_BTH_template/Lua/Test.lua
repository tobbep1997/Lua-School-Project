

if KeyBoardState == "A" then
	MovePlayer(-1, 0)
end
if KeyBoardState == "D" then
	MovePlayer(1,0)
end
if KeyBoardState == "W" then
	MovePlayer(0,-1)
end
if KeyBoardState == "S" then
	MovePlayer(0,1)
end



PlayerHealth = getPlayerHealth()


PlayerSetHealth(24555)

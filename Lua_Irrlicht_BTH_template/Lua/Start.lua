timer = 0
loadMap()

bullet = 0
shootDelta = 0

function KeyBoardCheck ()
	if KeyBoardState == "A" then
		PlayerMove(-1 * speedMult * DELTA_TIME, 0)
	end
	if KeyBoardState == "D" then
		PlayerMove(1* speedMult * DELTA_TIME,0)
	end
	if KeyBoardState == "W" then
		PlayerMove(0,-1* speedMult * DELTA_TIME)
	end
	if KeyBoardState == "S" then
		PlayerMove(0,1* speedMult * DELTA_TIME)
	end 
	if KeyBoardStateReload == "R" then
		bullet = 0
	end
end
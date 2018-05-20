speedMult = 5.1

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

shootDelta = shootDelta + DELTA_TIME

PlayerHealth = PlayerGetHealth()

SetBulletText(bullet, PlayerHealth)

x ,y = PlayerGetPos()

if x > SCREEN_WIDTH then PlayerSetPos(0,y) end
if x < 0 then PlayerSetPos(SCREEN_WIDTH, y) end

if y > SCREEN_HEIGHT then PlayerSetPos(x,0) end
if y < 0 then PlayerSetPos(x, SCREEN_HEIGHT) end

--print(MouseX, MouseY)

x,y = PlayerGetCenter()

if MouseX ~= -1 and MouseY ~= -1 then
	if shootDelta >= 0.6 then
		if bullet < 60 then
			AddBullet(x-20,y-20,MouseX, MouseY)
			bullet = bullet + 1
		end
		shootDelta = 0
	end
end


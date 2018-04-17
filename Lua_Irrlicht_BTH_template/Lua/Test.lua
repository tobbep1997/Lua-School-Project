speedMult = 0.1

if KeyBoardState == "A" then
	PlayerMove(-1 * speedMult, 0)
end
if KeyBoardState == "D" then
	PlayerMove(1* speedMult,0)
end
if KeyBoardState == "W" then
	PlayerMove(0,-1* speedMult)
end
if KeyBoardState == "S" then
	PlayerMove(0,1* speedMult)
end 



PlayerHealth = PlayerGetHealth()

x ,y = PlayerGetPos()

if x > SCREEN_WIDTH then PlayerSetPos(0,y) end
if x < 0 then PlayerSetPos(SCREEN_WIDTH, y) end

if y > SCREEN_HEIGHT then PlayerSetPos(x,0) end
if y < 0 then PlayerSetPos(x, SCREEN_HEIGHT) end

if MouseX ~= -1 and MouseY ~= -1 then PlayerSetPos(MouseX, MouseY) end
--PlayerSetPos(0,0)
--if ()kuk end
--print(x, y)

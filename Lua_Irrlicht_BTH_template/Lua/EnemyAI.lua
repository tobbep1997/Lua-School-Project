posx1,posy1 = PlayerGetPos()
posx2,posy2 = EnemyGetPos()

EnemyMoveTowards(0.1,posx1,posy1,posx2,posy2)
if EnemyGetLenghtTo(posx1,posy1,posx2,posy2) < 25 then
	--PlayerSetHealth(0)
	--print(PlayerGetHealth())
end

--print(b)
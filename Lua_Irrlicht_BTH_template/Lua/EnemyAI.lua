posx1,posy1 = PlayerGetPos()
--posx2,posy2 = EnemyGetPos()

posx2 = LocalEnemyPosX
posy2 = LocalEnemyPosY

--EnemyMoveTowards(0.1,posx1,posy1,LocalEnemyPosX,LocalEnemyPosY)
EnemyMoveTowards(1.1 * DELTA_TIME ,posx1,posy1,posx2,posy2)
if LuaGetLenghtTo(posx1,posy1,LocalEnemyPosX,LocalEnemyPosY) < 30 then
	PlayerTakeDamage(50)
	print(PlayerGetHealth())
	EnemySetExploded(true)
end


--print(b)
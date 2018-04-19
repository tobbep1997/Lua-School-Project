posx1,posy1 = PlayerGetPos()
--posx2,posy2 = EnemyGetPos()

posx2 = LocalEnemyPosX
posy2 = LocalEnemyPosY

print(posx2, " ", posy2)
--EnemyMoveTowards(0.1,posx1,posy1,LocalEnemyPosX,LocalEnemyPosY)
EnemyMoveTowards(0.1,posx1,posy1,posx2,posy2)
if LuaGetLenghtTo(posx1,posy1,LocalEnemyPosX,LocalEnemyPosY) < 25 then
	--PlayerTakeDamage(EnemyGetAttack())
	print(PlayerGetHealth())
end

--print(b)
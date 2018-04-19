posx1,posy1 = PlayerGetPos()
posx2,posy2 = EnemyGetPos()

EnemyMoveTowards(0.1,posx1,posy1,posx2,posy2)
if LuaGetLenghtTo(posx1,posy1,posx2,posy2) < 25 then
	--PlayerTakeDamage(EnemyGetAttack())
	print(PlayerGetHealth())
end

--print(b)
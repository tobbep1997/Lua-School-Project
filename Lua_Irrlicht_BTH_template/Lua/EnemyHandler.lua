timer = timer + DELTA_TIME

if timer > 0.5 * 50 then
	AddEnemy(Rand(0, SCREEN_WIDTH), Rand(0, SCREEN_HEIGHT))
	timer = 0
end
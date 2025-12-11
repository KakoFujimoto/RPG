#include"StatusWindowRenderer.h"


StatusWindowRenderer::StatusWindowRenderer(Display& d) : display(d) {}

void StatusWindowRenderer::draw() {
	if (!target) {
		return;
	}
	int col = GetColor(255, 255, 255);

	display.drawWindow(posX, posY, 250, 180, GetColor(255, 255, 255), GetColor(0, 0, 0));

	display.drawText(posX + 10, posY + 20, "‚È‚Ü‚¦: " + target->name, col);
	display.drawText(posX + 10, posY + 40, "HP: " + std::to_string(target->hp), col);
	display.drawText(posX + 10, posY + 60, "MP: " + std::to_string(target->mp), col);
	display.drawText(posX + 10, posY + 80, "‚±‚¤‚°‚«—Í: " + std::to_string(target->attackPower), col);
	display.drawText(posX + 10, posY + 100, "‚Ú‚¤‚¬‚å—Í: " + std::to_string(target->defensePower), col);
	display.drawText(posX + 10, posY + 120, "‚·‚Î‚â‚³: " + std::to_string(target->speed), col);
	display.drawText(posX + 10, posY + 140, "Lv: " + std::to_string(target->level), col);
	display.drawText(posX + 10, posY + 160, "‚¯‚¢‚¯‚ñ‚¿: " + std::to_string(target->gainedExp), col);
}
void StatusWindowRenderer::setTarget(const AllyParameter* p)
{
	target = p;
}

void StatusWindowRenderer::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

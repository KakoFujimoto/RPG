#include"StatusWindowRenderer.h"

StatusWindowRenderer::StatusWindowRenderer(Display& d) : display(d) {}

void StatusWindowRenderer::show(const AllyParameter& p, int x, int y) {
	display.drawWindow(x, y, 250, 180, GetColor(255, 255, 255), GetColor(0, 0, 0));
	int col = GetColor(255, 255, 255);
	display.drawText(x + 10, y + 20, "Name: " + p.name, col);
	display.drawText(x + 10, y + 40, "HP: " + std::to_string(p.hp), col);
	display.drawText(x + 10, y + 60, "MP: " + std::to_string(p.mp), col);
	display.drawText(x + 10, y + 80, "‚±‚¤‚°‚«—Í: " + std::to_string(p.attackPower), col);
	display.drawText(x + 10, y + 100, "‚Ú‚¤‚¬‚å—Í: " + std::to_string(p.defensePower), col);
	display.drawText(x + 10, y + 120, "‚·‚Î‚â‚³: " + std::to_string(p.speed), col);
	display.drawText(x + 10, y + 140, "Lv: " + std::to_string(p.level), col);
	display.drawText(x + 10, y + 160, "‚¯‚¢‚¯‚ñ‚¿: " + std::to_string(p.gainedExp), col);
}
#include "Anti-thetic.h"

void AntiThetic::SetDimensionality(unsigned long long NewDim)
{
	InnerGenerator->SetDimensionality(NewDim);
	DrawAntiThetic = false;
}

void AntiThetic::SetSeed(unsigned int NewSeed)
{
	InnerGenerator->SetSeed(NewSeed);
	DrawAntiThetic = false;
}

void AntiThetic::GetUniformDraw(std::vector<double>& Draws)
{
	if (DrawAntiThetic) {
		for (int i = 0;i<InnerGenerator->GetDimensionality();
			++i) {
			Draws[i] = 1 - PreviousDraw[i];
		}
		DrawAntiThetic = false;
	}
	else {
		InnerGenerator->GetUniformDraw(Draws);
		PreviousDraw = Draws;
		DrawAntiThetic = true;
	}
}

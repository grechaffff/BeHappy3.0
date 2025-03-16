#pragma once
#include"../src/BaseWindow.h"

class ShopManager  : public BaseWindow
{

private:



public:

	ShopManager();	
	void Render() override;

	void AddBanner();
	void ExitWindow();
	void UpdateLogo();
	void GoodsManag();
	void Settings();
	void Community();
	void StatisticsInfo();
	void OtherInfo();
};
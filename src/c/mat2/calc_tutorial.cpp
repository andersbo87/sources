// wGui Calculator tutorial

#include "wgui.h"
#include <iostream>

using namespace std;
using namespace wGui;


// Classes

class CCalcView : public CView
{
public:
	CCalcView(void);
	bool HandleMessage(CMessage* pMessage);

private:
	void UpdateDisplay(void);
	void DoCalc(void);

	CButton* m_pBtnNum[10];
	CButton* m_pBtnClear;
	CButton* m_pBtnEquals;
	CButton* m_pBtnPlus;
	CButton* m_pBtnMinus;
	CEditBox* m_pDisplay;
	int m_iDisplay;
	int m_iRegister;
	enum ECalcMode {
		MODE_NOP,
		MODE_ADD,
		MODE_SUB
	} m_eCalcMode;
};


class CCalcApp : public CApplication
{
public:
	CCalcApp(int argc, char **argv) : CApplication(argc, argv) { }

	virtual void Init(void)
	{
		CApplication::Init();
		SetDefaultFontEngine(GetFontEngine("Vera.ttf"));
	}
};


// Main

int main(int argc, char **argv)
{
	int iExitCode = EXIT_FAILURE;
	try
	{
		CCalcApp CalcApp(argc, argv);
		CalcApp.Init();

		CCalcView CalcView;
		CalcApp.Exec();

		iExitCode = CalcApp.ExitCode();
	}
	catch (Wg_Ex_Base& e)
	{
		cerr << "Unhandled wGui exception : " << e.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (exception& e)
	{
		cerr << "Unhandled std exception : " << e.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (...)
	{
		cerr << "Unhandled exception." << endl;
		exit(EXIT_FAILURE);
	}
	exit (iExitCode);
}


// Class methods

CCalcView::CCalcView(void) :
	CView(CRect(0, 0, 170, 210), "wGui Calculator Tutorial", false),
	m_iDisplay(0),
	m_iRegister(0),
	m_eCalcMode(MODE_NOP)
{
	CMessageServer::Instance().RegisterMessageClient(this, CMessage::CTRL_SINGLELCLICK);
	m_pDisplay = new CEditBox(CRect(10, 10, 150, 30), this);
	m_pDisplay->SetWindowText("0");
	m_pDisplay->SetReadOnly(true);
	m_pBtnNum[7] = new CButton(CRect(10, 50, 40, 80), this, "7");
	m_pBtnNum[8] = new CButton(CRect(50, 50, 80, 80), this, "8");
	m_pBtnNum[9] = new CButton(CRect(90, 50, 120, 80), this, "9");
	m_pBtnClear = new CButton(CRect(130, 50, 160, 80), this, "C");
	m_pBtnNum[4] = new CButton(CRect(10, 90, 40, 120), this, "4");
	m_pBtnNum[5] = new CButton(CRect(50, 90, 80, 120), this, "5");
	m_pBtnNum[6] = new CButton(CRect(90, 90, 120, 120), this, "6");
	m_pBtnPlus = new CButton(CRect(130, 90, 160, 120), this, "+");
	m_pBtnNum[1] = new CButton(CRect(10, 130, 40, 160), this, "1");
	m_pBtnNum[2] = new CButton(CRect(50, 130, 80, 160), this, "2");
	m_pBtnNum[3] = new CButton(CRect(90, 130, 120, 160), this, "3");
	m_pBtnMinus = new CButton(CRect(130, 130, 160, 160), this, "-");
	m_pBtnNum[0] = new CButton(CRect(10, 170, 40, 200), this, "0");
	m_pBtnEquals = new CButton(CRect(50, 170, 120, 200), this, "=");
}




bool CCalcView::HandleMessage(CMessage* pMessage)
{
	bool bHandled = false;

	if (pMessage)
	{
		switch (pMessage->MessageType())
		{
		case CMessage::CTRL_SINGLELCLICK:
			if (pMessage->Destination() == this)
			{
				bHandled = true;
				const wGui::CMessageClient* pSource = pMessage->Source();
				if (pSource == m_pBtnClear)
				{
					m_iDisplay = 0;
					m_iRegister = 0;
					m_eCalcMode = MODE_NOP;
				}
				else if (pSource == m_pBtnPlus)
				{
					DoCalc();
					m_iRegister = m_iDisplay;
					m_iDisplay = 0;
					m_eCalcMode = MODE_ADD;
				}
				else if (pSource == m_pBtnMinus)
				{
					DoCalc();
					m_iRegister = m_iDisplay;
					m_iDisplay = 0;
					m_eCalcMode = MODE_SUB;
				}
				else if (pSource == m_pBtnEquals)
				{
					DoCalc();
					m_iRegister = 0;
					m_eCalcMode = MODE_NOP;
				}
				else if (pSource != 0)
				{
					bHandled = false;
					for (int i = 0; i <= 9; ++i)
					{
						if (pSource == m_pBtnNum[i])
						{
							m_iDisplay = m_iDisplay * 10 + i;
							bHandled = true;
							break; //exit for loop
						}
					}
				}
				UpdateDisplay();
			}
			break;
		default:
			bHandled = CView::HandleMessage(pMessage);
			break;
		}
	}

	return bHandled;
}


void CCalcView::UpdateDisplay(void)
{
	char cMode = m_eCalcMode == MODE_ADD ? '+' :
		m_eCalcMode == MODE_SUB ? '-' : ' ';
	char buffer[100];
	sprintf(buffer, "%i %c", m_iDisplay, cMode);
	m_pDisplay->SetWindowText(buffer);
}


void CCalcView::DoCalc(void)
{
	switch (m_eCalcMode)
	{
	case MODE_ADD:
		m_iDisplay = m_iRegister + m_iDisplay;
		break;
	case MODE_SUB:
		m_iDisplay = m_iRegister - m_iDisplay;
		break;
	default:
		break;
	}
}

// ResearchKeeper.h: interface for the ResearchKeeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESEARCHKEEPER_H__EB5873B2_779A_405B_94BD_433828D61B8D__INCLUDED_)
#define AFX_RESEARCHKEEPER_H__EB5873B2_779A_405B_94BD_433828D61B8D__INCLUDED_

class ResearchTechnics;
class GameData;

class ResearchKeeper  
{
private:
  std::vector<ResearchTechnics*> entry_researchs_;
  GameData* data_;
  
public:
	ResearchKeeper(GameData* d);
	virtual ~ResearchKeeper();
  ResearchTechnics* GetResearch(int index);
  int Size() {return entry_researchs_.size();}

private:
  void CreateResearchs();

};

#endif // !defined(AFX_RESEARCHKEEPER_H__EB5873B2_779A_405B_94BD_433828D61B8D__INCLUDED_)

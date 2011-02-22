#include "FSM.h"
#include "Common.h"
using namespace std;
using namespace NS_RUN;
using namespace Ogre;

Fsm::Fsm()
{
    mCurState = 0;
    mMapStates.clear();
}

Fsm::~Fsm()
{
    MAP_STATE::iterator iterDel = mMapStates.begin();
    for(;iterDel != mMapStates.end(); ++iterDel)
    {
        delete iterDel->second;
    }
    mMapStates.clear();
}

void Fsm::AddState(IState* pState)
{
    MAP_STATE::iterator iterFind = mMapStates.find(pState->GetStateId());
    if(iterFind != mMapStates.end())
    {
        char LogChars[512];
        sprintf(LogChars,"ERROR: AddState add a exiting State ,stateId %d", pState->GetStateId());
        mpLog->logMessage(LogChars, LML_CRITICAL);
        IState *oldState = mMapStates[pState->GetStateId()] ;
        oldState->SwitchOut();
        delete oldState;
    }
    
    mMapStates[pState->GetStateId()] = pState;
}

void Fsm::SwitchState(int toStateId)
{
    MAP_STATE::iterator iterFind = mMapStates.find(toStateId);
    if(iterFind == mMapStates.end())
    {
        char LogChars[512];
        sprintf(LogChars,"ERROR: SwitchState to No exit State,stateId %d", toStateId);
        mpLog->logMessage(LogChars, LML_CRITICAL);
        return;
    }
    if(!mCurState)
    {
        mCurState = iterFind->second;
        mCurState->SwitchIn();
    }
    else
    {
        mCurState->SwitchOut();
        mCurState = iterFind->second;
        mCurState->SwitchIn();
    }
    char LogChars[512];
    sprintf(LogChars, "Switch State to: %d", toStateId);
    mpLog->logMessage(LogChars);
}

void Fsm::Update( const FrameEvent& evt)
{
    if(mCurState)
    {
        mCurState->Update(evt);
    }
}
 
bool Fsm::keyPressed( const OIS::KeyEvent &arg )
{
    if(mCurState)
    {
        return mCurState->keyPressed(arg);
    }
    return false;
}

bool Fsm::keyReleased( const OIS::KeyEvent &arg )
{
    if(mCurState)
    {
        return mCurState->keyReleased(arg);
    }
    return false;
}
 


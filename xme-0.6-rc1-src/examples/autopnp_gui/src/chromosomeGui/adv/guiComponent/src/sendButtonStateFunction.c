/*
 * Copyright (c) 2011-2013, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id$
 */

/**
 * \file
 *         Source file for function sendButtonState in component guiComponent.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "chromosomeGui/adv/guiComponent/include/sendButtonStateFunction.h"

#include "chromosomeGui/adv/guiComponent/include/sendButtonStateFunctionWrapper.h"
#include "chromosomeGui/adv/guiComponent/include/guiComponentComponentWrapper.h"

// PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_C_INCLUDES) ENABLED START
#include "wrapperHeader.h"
#include "xme/hal/include/mem.h"
#include "headerFile.h"
#include <pthread.h>

#include <unistd.h>
//#include <boost/thread/thread.hpp>

//#include <Windows.h>
// PROTECTED REGION END

/******************************************************************************/
/***   Static variables                                                     ***/
/******************************************************************************/
/**
 * \brief  Variable holding the value of the optional output port 'buttonPushed'.
 *
 * \details If necessary initialize this in the init function.
 *          The value of this variable will be written to the port at the end of
 *          the step function.
 */
static chromosomeGui_topic_ButtonSignal_t
portButtonPushedData;

// PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_C_STATICVARIABLES) ENABLED START
static int buttonState;
static int terminateApplicationValue;
/*
 * Added these lines to create the GUI thread
 */
typedef struct
{
	int argc;
	char *argv[];
}threadData_t;

/* this variable is our reference to the thread */
static pthread_t thread_ref, ros_thread_ref;

/******************************************************************************/
/***   Helper function                                                     ***/
/******************************************************************************/

void
writeButtonState
(
    int buttonPushed
)
{
    buttonState = buttonPushed;
}

void terminateApplicationCall(void)
{
	terminateApplicationValue = 1;
}

/*
 * Added these lines to create the GUI thread
 */
//static unsigned int startGuiThread( void* lpParam );
////End insertion
//
///*
// * Added these lines to create the GUI thread
// */
//static unsigned int startGuiThread( void* lpParam )
//{
//	//printf("Starting thread\n");
//	threadData_t *data = (threadData_t*)lpParam;
//	startGui(data->argc, data->argv);
//
//    return 0;
//}
static void* startGuiThread( void* lpParam );
/*
 * Added these lines to create the GUI thread
 */
static void* startGuiThread( void* lpParam )
{ 
	//printf("Starting thread\n");
	threadData_t *data = (threadData_t*)lpParam;
	startGui(data->argc, data->argv);

    return NULL;
}

static void* initRosThread( void* lpParam );
/*
 * Added these lines to create the GUI thread
 */
static void* initRosThread( void* lpParam )
{
	//printf("Starting thread\n");
	threadData_t *data = (threadData_t*)lpParam;
	initRos(data->argc, data->argv);

    return NULL;
}
// PROTECTED REGION END

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
chromosomeGui_adv_guiComponent_sendButtonStateFunction_init
(
    void* param
)
{
    // PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_INITIALIZE_C) ENABLED START
    /*
	 * Added these lines to create the GUI thread
	 */
	//void* guiThread;
	//unsigned int threadId;
	threadData_t* threadData;
    char text = 'C';
    int ret_thread;
    int ret_ros_thread;

    buttonState = 0;
    terminateApplicationValue = 0;
	//End insertion
    /*
	 * Added these lines to create the GUI thread
	 */
	threadData = (threadData_t*)xme_hal_mem_alloc(sizeof(threadData_t));
	threadData->argc = 1;
    
	threadData->argv[0] = &text;

	/* create a thread */
	if (pthread_create(&thread_ref, NULL, startGuiThread, (void*)threadData))
	{
		fprintf(stderr, "Error creating startGuiThread\n");
		return 1;
	}

	/* create a thread */
	if (pthread_create(&ros_thread_ref, NULL, initRosThread, (void*)threadData))
	{
		fprintf(stderr, "Error creating initRosThread\n");
		return 1;
	}

	fprintf(stdout, "All threads running.\n");
	while (terminateApplicationValue == 0)
		sleep(0.01);

	fprintf(stdout, "Terminating Application.\n");
	ret_thread = pthread_join(thread_ref, NULL);
	fprintf(stdout, "Gui thread return value = %i.\n", ret_thread);
	ret_ros_thread = pthread_join(ros_thread_ref, NULL);
	fprintf(stdout, "ROS thread return valus %i.\n", ret_ros_thread);

	terminateApplicationValue = 2;

//	guiThread = CreateThread(NULL, 0, (/*LPTHREAD_START_ROUTINE*/void*) &startGuiThread, (void*)threadData, 0, &threadId);
	//End insertion
    // TODO: Auto-generated stub
    
    XME_UNUSED_PARAMETER(param);
    
    return XME_STATUS_SUCCESS;
    
    // PROTECTED REGION END
}

void
chromosomeGui_adv_guiComponent_sendButtonStateFunction_step
(
    void* param
)
{
    xme_status_t status[1];
    
    chromosomeGui_topic_ButtonSignal_t* portButtonPushedDataPtr = &portButtonPushedData;
    
    {
        // PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_STEP_C) ENABLED START
		int state = 1;
		portButtonPushedData.buttonPushed = 0;
        // TODO: Auto-generated stub
    
        XME_UNUSED_PARAMETER(param);
        XME_UNUSED_PARAMETER(status);

		if(buttonState == 1)
		{
			XME_LOG(XME_LOG_ALWAYS, "Button was pressed\n");
			portButtonPushedData.buttonPushed = state;
			buttonState = 0;
		}

		if (terminateApplicationValue==2)
			exit(0);
        
        // PROTECTED REGION END
    }
    
    status[0] = chromosomeGui_adv_guiComponent_guiComponentComponentWrapper_writePortButtonPushed(portButtonPushedDataPtr);
    
    {
        // PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_STEP_2_C) ENABLED START
    
        // TODO: Auto-generated stub
        //       Check return values of writePort calls here
    
        // PROTECTED REGION END
    }
}

void
chromosomeGui_adv_guiComponent_sendButtonStateFunction_fini(void)
{
    // PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_TERMINATE_C) ENABLED START
    
    // TODO: Auto-generated stub
    
    // PROTECTED REGION END
}

// PROTECTED REGION ID(CHROMOSOMEGUI_ADV_GUICOMPONENT_SENDBUTTONSTATEFUNCTION_IMPLEMENTATION_C) ENABLED START

// PROTECTED REGION END
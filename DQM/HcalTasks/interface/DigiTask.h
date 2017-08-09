#ifndef DigiTask_h
#define DigiTask_h

/**
 *	file:			DigiTask.h
 *	Author:			VK
 *	Description:
 *		HCAL DIGI Data Tier Processing.
 *
 *	Online:
 *		
 *	Offline:
 *		- HF Q2/(Q1+Q2) is not included.
 */

#include "DQM/HcalCommon/interface/DQTask.h"
#include "DQM/HcalCommon/interface/Utilities.h"
#include "DQM/HcalCommon/interface/HashFilter.h"
#include "DQM/HcalCommon/interface/ElectronicsMap.h"
#include "DQM/HcalCommon/interface/Container1D.h"
#include "DQM/HcalCommon/interface/Container2D.h"
#include "DQM/HcalCommon/interface/ContainerProf1D.h"
#include "DQM/HcalCommon/interface/ContainerProf2D.h"
#include "DQM/HcalCommon/interface/ContainerSingle1D.h"
#include "DQM/HcalCommon/interface/ContainerSingle2D.h"
#include "DQM/HcalCommon/interface/ContainerSingleProf2D.h"
#include "DQM/HcalCommon/interface/ContainerXXX.h"

class DigiTask : public hcaldqm::DQTask
{
	public:
		DigiTask(edm::ParameterSet const&);
		virtual ~DigiTask() {}

		virtual void bookHistograms(DQMStore::IBooker&,
			edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&,
			edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&,
			edm::EventSetup const&);

	protected:
		virtual void _process(edm::Event const&, edm::EventSetup const&);
		virtual void _resetMonitors(hcaldqm::UpdateFreq);

		edm::InputTag		_tagHBHE;
		edm::InputTag		_tagHEP17;
		edm::InputTag		_tagHO;
		edm::InputTag		_tagHF;
		edm::EDGetTokenT<HBHEDigiCollection> _tokHBHE;
		edm::EDGetTokenT<QIE11DigiCollection> _tokHEP17;
		edm::EDGetTokenT<HODigiCollection>	 _tokHO;
		edm::EDGetTokenT<QIE10DigiCollection>	_tokHF;

		double _cutSumQ_HBHE, _cutSumQ_HEP17, _cutSumQ_HO, _cutSumQ_HF;
		double _thresh_unihf;

		//	flag vector
		std::vector<hcaldqm::flag::Flag> _vflags;
		enum DigiFlag
		{
			fDigiSize=0,
			fUni = 1,
			fNChsHF = 2,
			fUnknownIds = 3,
			nDigiFlag = 4
		};

		//	hashes/FED vectors
		std::vector<uint32_t> _vhashFEDs;

		//	emap
		hcaldqm::electronicsmap::ElectronicsMap _ehashmap; // online only
		hcaldqm::electronicsmap::ElectronicsMap _dhashmap;

		//	Filters
		hcaldqm::filter::HashFilter _filter_VME;
		hcaldqm::filter::HashFilter _filter_uTCA;
		hcaldqm::filter::HashFilter _filter_FEDHF;
		hcaldqm::filter::HashFilter _filter_HF;
		hcaldqm::filter::HashFilter _filter_notHF;
		hcaldqm::filter::HashFilter _filter_HEP17;

		/* hcaldqm::Containers */
		//	ADC, fC - Charge - just filling - no summary!
		hcaldqm::Container1D _cADC_SubdetPM;
		hcaldqm::Container1D _cfC_SubdetPM;
		hcaldqm::Container1D _cSumQ_SubdetPM;
		hcaldqm::ContainerProf2D	_cSumQ_depth;
		hcaldqm::ContainerProf1D _cSumQvsLS_SubdetPM;
		hcaldqm::ContainerProf1D _cSumQvsBX_SubdetPM;	// online only!

		// ADC, fC for HF (QIE10 has different ADC/fC)
		hcaldqm::Container1D _cADC_SubdetPM_HF;
		hcaldqm::Container1D _cfC_SubdetPM_HF;
		hcaldqm::Container1D _cSumQ_SubdetPM_HF;
		hcaldqm::ContainerProf1D _cSumQvsLS_SubdetPM_HF;
		hcaldqm::ContainerProf1D _cSumQvsBX_SubdetPM_HF;	// online only!

		
		//	Shape - just filling - not summary!
		hcaldqm::Container1D _cShapeCut_FED;
		hcaldqm::Container2D _cADCvsTS_SubdetPM;
		hcaldqm::Container2D _cADCvsTS_SubdetPM_HF;

		//	Timing
		//	just filling - no summary!
		hcaldqm::Container1D		_cTimingCut_SubdetPM;
		hcaldqm::ContainerProf2D _cTimingCut_FEDVME;
		hcaldqm::ContainerProf2D	_cTimingCut_FEDuTCA;
		hcaldqm::ContainerProf2D _cTimingCut_ElectronicsVME;
		hcaldqm::ContainerProf2D _cTimingCut_ElectronicsuTCA;
		hcaldqm::ContainerProf1D _cTimingCutvsLS_FED;
		hcaldqm::ContainerProf1D _cTimingCutvsLS_SubdetPM;
		hcaldqm::ContainerProf2D _cTimingCut_depth;
		hcaldqm::ContainerProf1D _cTimingCutvsiphi_SubdetPM;	// online only!
		hcaldqm::ContainerProf1D _cTimingCutvsieta_Subdet;	// online only!

		//	Only for Online mode! just filling - no summary!
		hcaldqm::ContainerProf1D _cQ2Q12CutvsLS_FEDHF;	//	online only!

		//	Occupancy w/o a Cut - whatever is sitting in the Digi Collection
		//	used to determine Missing Digis => used for Summary!
		hcaldqm::Container2D _cOccupancy_FEDVME;
		hcaldqm::Container2D _cOccupancy_FEDuTCA;
		hcaldqm::Container2D _cOccupancy_ElectronicsVME;
		hcaldqm::Container2D _cOccupancy_ElectronicsuTCA;
		hcaldqm::Container2D _cOccupancy_Crate;
		hcaldqm::Container2D _cOccupancy_CrateSlot;
		hcaldqm::Container2D _cOccupancy_depth;
		hcaldqm::Container1D _cOccupancyvsiphi_SubdetPM; // online only
		hcaldqm::Container1D _cOccupancyvsieta_Subdet;	// online only

		//	Occupancy w/ a Cut
		//	used to determine if occupancy is symmetric or not. =>
		//	used for Summary
		hcaldqm::Container2D _cOccupancyCut_FEDVME;
		hcaldqm::Container2D _cOccupancyCut_FEDuTCA;
		hcaldqm::Container2D _cOccupancyCut_ElectronicsVME;
		hcaldqm::Container2D _cOccupancyCut_ElectronicsuTCA;
		hcaldqm::Container2D _cOccupancyCut_depth;
		hcaldqm::Container1D _cOccupancyCutvsiphi_SubdetPM; // online only
		hcaldqm::Container1D _cOccupancyCutvsieta_Subdet;	// online only
		hcaldqm::Container2D _cOccupancyCutvsSlotvsLS_HFPM; // online only
		hcaldqm::Container2D _cOccupancyCutvsiphivsLS_SubdetPM; // online only

		//	Occupancy w/o and w/ a Cut vs BX and vs LS
		hcaldqm::ContainerProf1D _cOccupancyvsLS_Subdet;
		hcaldqm::ContainerProf1D _cOccupancyCutvsLS_Subdet;	// online only
		hcaldqm::ContainerProf1D _cOccupancyCutvsBX_Subdet;	// online only

		//	#Time Samples for a digi. Used for Summary generation
		hcaldqm::Container1D _cDigiSize_Crate;
		hcaldqm::Container1D _cDigiSize_FED;
		hcaldqm::ContainerProf1D _cDigiSizevsLS_FED;	// online only
		hcaldqm::ContainerXXX<uint32_t> _xDigiSize; // online only
		hcaldqm::ContainerXXX<uint32_t> _xUniHF,_xUni; // online only
		hcaldqm::ContainerXXX<uint32_t> _xNChs; // online only
		hcaldqm::ContainerXXX<uint32_t> _xNChsNominal; // online only

		// QIE10 TDC histograms
		hcaldqm::Container2D _cLETDCTimevsADC_SubdetPM;
		hcaldqm::Container2D _cLETDCvsADC_SubdetPM;
		hcaldqm::Container2D _cLETDCvsTS_SubdetPM;
		hcaldqm::Container1D _cLETDCTime_SubdetPM;

		//	#events counters
		MonitorElement *meNumEvents1LS; // to transfer the #events to harvesting
		MonitorElement *meUnknownIds1LS;
		bool _unknownIdsPresent;

		hcaldqm::Container2D _cSummaryvsLS_FED; // online only
		hcaldqm::ContainerSingle2D _cSummaryvsLS; // online only

		bool _qie10InConditions; // Flag to protect against QIE10 digis not in conditions in 2016.
};

#endif
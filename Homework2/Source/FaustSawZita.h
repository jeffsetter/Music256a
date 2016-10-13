/* ------------------------------------------------------------
author: "CL GRAME and modified by Jeff Setter"
copyright: "(c)GRAME 2013"
license: "BSD"
name: "EK_Verb2"
version: "0.1"
Code generated with Faust 2.0.a51 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#include <math.h>


class mydspSIG0 {
	
  private:
	
	int iRec8[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
		
	}
	int getNumOutputsmydspSIG0() {
		return 1;
		
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitmydspSIG0(int samplingFreq) {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iRec8[i0] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec8[0] = (iRec8[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec8[0] + -1))));
			iRec8[1] = iRec8[0];
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];
float faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int iConst29;
	int iConst28;
	int iConst24;
	int iConst23;
	int iConst19;
	int iConst18;
	int iConst14;
	int iConst13;
	int iConst8;
	int IOTA;
	int fSamplingFreq;
	float fVec5[16384];
	float fVec7[16384];
	float fVec0[8192];
	float fVec1[8192];
	float fVec3[8192];
	float fVec4[2048];
	float fVec6[2048];
	float fVec8[2048];
	float fVec2[1024];
	float fRec1[3];
	float fRec0[3];
	float fRec27[3];
	float fRec26[3];
	float fRec10[2];
	float fRec9[2];
	float fRec12[2];
	float fRec11[2];
	float fRec13[2];
	float fRec14[2];
	float fRec16[2];
	float fRec15[2];
	float fRec6[2];
	float fRec19[2];
	float fRec17[2];
	float fRec22[2];
	float fRec20[2];
	float fRec25[2];
	float fRec23[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fButton0;
	float fConst9;
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider3;
	float fConst12;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "CL GRAME and modified by Jeff Setter");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2013");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
		m->declare("name", "EK_Verb2");
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("route.lib/name", "Faust Signal Routing Library");
		m->declare("route.lib/version", "0.0");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("version", "0.1");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (329.867218f * (fConst1 / sinf((1979.20337f * fConst1))));
		fConst3 = tanf((989.601685f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (1.0f / (((fConst2 + fConst4) / fConst3) + 1.0f));
		fConst6 = (((fConst4 - fConst2) / fConst3) + 1.0f);
		fConst7 = (1.0f / fConst0);
		iConst8 = (int((0.0500000007f * fConst0)) & 8191);
		fConst9 = cosf((50265.4844f / fConst0));
		fConst10 = floorf(((0.153128996f * fConst0) + 0.5f));
		fConst11 = ((0.0f - (6.90775537f * fConst10)) / fConst0);
		fConst12 = floorf(((0.0203460008f * fConst0) + 0.5f));
		iConst13 = (int((fConst10 - fConst12)) & 8191);
		iConst14 = (int((fConst12 + -1.0f)) & 1023);
		fConst15 = floorf(((0.127837002f * fConst0) + 0.5f));
		fConst16 = ((0.0f - (6.90775537f * fConst15)) / fConst0);
		fConst17 = floorf(((0.0316039994f * fConst0) + 0.5f));
		iConst18 = (int((fConst15 - fConst17)) & 8191);
		iConst19 = (int((fConst17 + -1.0f)) & 2047);
		fConst20 = floorf(((0.210389003f * fConst0) + 0.5f));
		fConst21 = ((0.0f - (6.90775537f * fConst20)) / fConst0);
		fConst22 = floorf(((0.0244210009f * fConst0) + 0.5f));
		iConst23 = (int((fConst20 - fConst22)) & 16383);
		iConst24 = (int((fConst22 + -1.0f)) & 2047);
		fConst25 = floorf(((0.256891012f * fConst0) + 0.5f));
		fConst26 = ((0.0f - (6.90775537f * fConst25)) / fConst0);
		fConst27 = floorf(((0.0273330007f * fConst0) + 0.5f));
		iConst28 = (int((fConst25 - fConst27)) & 16383);
		iConst29 = (int((fConst27 + -1.0f)) & 2047);
		fConst30 = (2.0f * (1.0f - (1.0f / faustpower2_f(fConst3))));
		fConst31 = (3141.59277f * (fConst1 / sinf((18849.5566f * fConst1))));
		fConst32 = tanf((9424.77832f / fConst0));
		fConst33 = (1.0f / fConst32);
		fConst34 = (1.0f / (((fConst31 + fConst33) / fConst32) + 1.0f));
		fConst35 = (((fConst33 - fConst31) / fConst32) + 1.0f);
		fConst36 = (2.0f * (1.0f - (1.0f / faustpower2_f(fConst32))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(440.0f);
		fHslider1 = FAUSTFLOAT(440.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(1.5f);
		
	}
	
	virtual void instanceClear() {
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec10[i1] = 0.0f;
			
		}
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec9[i2] = 0.0f;
			
		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			fRec12[i3] = 0.0f;
			
		}
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			fRec11[i4] = 0.0f;
			
		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			fRec13[i5] = 0.0f;
			
		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			fRec14[i6] = 0.0f;
			
		}
		IOTA = 0;
		for (int i7 = 0; (i7 < 8192); i7 = (i7 + 1)) {
			fVec0[i7] = 0.0f;
			
		}
		for (int i8 = 0; (i8 < 2); i8 = (i8 + 1)) {
			fRec16[i8] = 0.0f;
			
		}
		for (int i9 = 0; (i9 < 2); i9 = (i9 + 1)) {
			fRec15[i9] = 0.0f;
			
		}
		for (int i10 = 0; (i10 < 8192); i10 = (i10 + 1)) {
			fVec1[i10] = 0.0f;
			
		}
		for (int i11 = 0; (i11 < 1024); i11 = (i11 + 1)) {
			fVec2[i11] = 0.0f;
			
		}
		for (int i12 = 0; (i12 < 2); i12 = (i12 + 1)) {
			fRec6[i12] = 0.0f;
			
		}
		for (int i13 = 0; (i13 < 2); i13 = (i13 + 1)) {
			fRec19[i13] = 0.0f;
			
		}
		for (int i14 = 0; (i14 < 8192); i14 = (i14 + 1)) {
			fVec3[i14] = 0.0f;
			
		}
		for (int i15 = 0; (i15 < 2048); i15 = (i15 + 1)) {
			fVec4[i15] = 0.0f;
			
		}
		for (int i16 = 0; (i16 < 2); i16 = (i16 + 1)) {
			fRec17[i16] = 0.0f;
			
		}
		for (int i17 = 0; (i17 < 2); i17 = (i17 + 1)) {
			fRec22[i17] = 0.0f;
			
		}
		for (int i18 = 0; (i18 < 16384); i18 = (i18 + 1)) {
			fVec5[i18] = 0.0f;
			
		}
		for (int i19 = 0; (i19 < 2048); i19 = (i19 + 1)) {
			fVec6[i19] = 0.0f;
			
		}
		for (int i20 = 0; (i20 < 2); i20 = (i20 + 1)) {
			fRec20[i20] = 0.0f;
			
		}
		for (int i21 = 0; (i21 < 2); i21 = (i21 + 1)) {
			fRec25[i21] = 0.0f;
			
		}
		for (int i22 = 0; (i22 < 16384); i22 = (i22 + 1)) {
			fVec7[i22] = 0.0f;
			
		}
		for (int i23 = 0; (i23 < 2048); i23 = (i23 + 1)) {
			fVec8[i23] = 0.0f;
			
		}
		for (int i24 = 0; (i24 < 2); i24 = (i24 + 1)) {
			fRec23[i24] = 0.0f;
			
		}
		for (int i25 = 0; (i25 < 2); i25 = (i25 + 1)) {
			fRec2[i25] = 0.0f;
			
		}
		for (int i26 = 0; (i26 < 2); i26 = (i26 + 1)) {
			fRec3[i26] = 0.0f;
			
		}
		for (int i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			fRec4[i27] = 0.0f;
			
		}
		for (int i28 = 0; (i28 < 2); i28 = (i28 + 1)) {
			fRec5[i28] = 0.0f;
			
		}
		for (int i29 = 0; (i29 < 3); i29 = (i29 + 1)) {
			fRec1[i29] = 0.0f;
			
		}
		for (int i30 = 0; (i30 < 3); i30 = (i30 + 1)) {
			fRec0[i30] = 0.0f;
			
		}
		for (int i31 = 0; (i31 < 3); i31 = (i31 + 1)) {
			fRec27[i31] = 0.0f;
			
		}
		for (int i32 = 0; (i32 < 3); i32 = (i32 + 1)) {
			fRec26[i32] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("ZitaReverb");
		ui_interface->openHorizontalBox("saw");
		ui_interface->addHorizontalSlider("decay", &fHslider3, 1.5f, 0.5f, 8.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq1", &fHslider0, 440.0f, 20.0f, 20000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq2", &fHslider1, 440.0f, 20.0f, 20000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("gain", &fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate",&fButton0);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = (0.00100000005f * float(fButton0));
		float fSlow4 = (0.00100000005f * float(fHslider3));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec10[0] = (fSlow0 + (0.999000013f * fRec10[1]));
			float fTemp0 = (fRec9[1] + (fConst7 * fRec10[0]));
			fRec9[0] = (fTemp0 - floorf(fTemp0));
			fRec12[0] = (fSlow1 + (0.999000013f * fRec12[1]));
			float fTemp1 = (fRec11[1] + (fConst7 * fRec12[0]));
			fRec11[0] = (fTemp1 - floorf(fTemp1));
			fRec13[0] = (fSlow2 + (0.999000013f * fRec13[1]));
			fRec14[0] = (fSlow3 + (0.999000013f * fRec14[1]));
			fVec0[(IOTA & 8191)] = (((ftbl0mydspSIG0[int((65536.0f * fRec9[0]))] + ftbl0mydspSIG0[int((65536.0f * fRec11[0]))]) * fRec13[0]) * fRec14[0]);
			float fTemp2 = (0.150000006f * fVec0[((IOTA - iConst8) & 8191)]);
			fRec16[0] = (fSlow4 + (0.999000013f * fRec16[1]));
			float fTemp3 = max(0.5f, min(6.0f, fRec16[0]));
			float fTemp4 = expf((fConst11 / fTemp3));
			float fTemp5 = faustpower2_f(fTemp4);
			float fTemp6 = (1.0f - (fConst9 * fTemp5));
			float fTemp7 = (1.0f - fTemp5);
			float fTemp8 = (fTemp6 / fTemp7);
			float fTemp9 = sqrtf(max(0.0f, ((faustpower2_f(fTemp6) / faustpower2_f(fTemp7)) + -1.0f)));
			fRec15[0] = ((fRec15[1] * (fTemp8 - fTemp9)) + ((fRec2[1] * fTemp4) * (fTemp9 + (1.0f - fTemp8))));
			fVec1[(IOTA & 8191)] = ((0.5f * fRec15[0]) + 9.99999968e-21f);
			float fTemp10 = ((fTemp2 + fVec1[((IOTA - iConst13) & 8191)]) - (0.600000024f * fRec6[1]));
			fVec2[(IOTA & 1023)] = fTemp10;
			fRec6[0] = fVec2[((IOTA - iConst14) & 1023)];
			float fRec7 = (0.600000024f * fTemp10);
			float fTemp11 = expf((fConst16 / fTemp3));
			float fTemp12 = faustpower2_f(fTemp11);
			float fTemp13 = (1.0f - (fConst9 * fTemp12));
			float fTemp14 = (1.0f - fTemp12);
			float fTemp15 = (fTemp13 / fTemp14);
			float fTemp16 = sqrtf(max(0.0f, ((faustpower2_f(fTemp13) / faustpower2_f(fTemp14)) + -1.0f)));
			fRec19[0] = ((fRec19[1] * (fTemp15 - fTemp16)) + ((fRec4[1] * fTemp11) * (fTemp16 + (1.0f - fTemp15))));
			fVec3[(IOTA & 8191)] = ((0.5f * fRec19[0]) + 9.99999968e-21f);
			float fTemp17 = (fVec3[((IOTA - iConst18) & 8191)] - (fTemp2 + (0.600000024f * fRec17[1])));
			fVec4[(IOTA & 2047)] = fTemp17;
			fRec17[0] = fVec4[((IOTA - iConst19) & 2047)];
			float fRec18 = (0.600000024f * fTemp17);
			float fTemp18 = expf((fConst21 / fTemp3));
			float fTemp19 = faustpower2_f(fTemp18);
			float fTemp20 = (1.0f - (fConst9 * fTemp19));
			float fTemp21 = (1.0f - fTemp19);
			float fTemp22 = (fTemp20 / fTemp21);
			float fTemp23 = sqrtf(max(0.0f, ((faustpower2_f(fTemp20) / faustpower2_f(fTemp21)) + -1.0f)));
			fRec22[0] = ((fRec22[1] * (fTemp22 - fTemp23)) + ((fRec3[1] * fTemp18) * (fTemp23 + (1.0f - fTemp22))));
			fVec5[(IOTA & 16383)] = ((0.5f * fRec22[0]) + 9.99999968e-21f);
			float fTemp24 = (fVec5[((IOTA - iConst23) & 16383)] + (fTemp2 + (0.600000024f * fRec20[1])));
			fVec6[(IOTA & 2047)] = fTemp24;
			fRec20[0] = fVec6[((IOTA - iConst24) & 2047)];
			float fRec21 = (0.0f - (0.600000024f * fTemp24));
			float fTemp25 = expf((fConst26 / fTemp3));
			float fTemp26 = faustpower2_f(fTemp25);
			float fTemp27 = (1.0f - (fConst9 * fTemp26));
			float fTemp28 = (1.0f - fTemp26);
			float fTemp29 = (fTemp27 / fTemp28);
			float fTemp30 = sqrtf(max(0.0f, ((faustpower2_f(fTemp27) / faustpower2_f(fTemp28)) + -1.0f)));
			fRec25[0] = ((fRec25[1] * (fTemp29 - fTemp30)) + ((fRec5[1] * fTemp25) * (fTemp30 + (1.0f - fTemp29))));
			fVec7[(IOTA & 16383)] = ((0.5f * fRec25[0]) + 9.99999968e-21f);
			float fTemp31 = (((0.600000024f * fRec23[1]) + fVec7[((IOTA - iConst28) & 16383)]) - fTemp2);
			fVec8[(IOTA & 2047)] = fTemp31;
			fRec23[0] = fVec8[((IOTA - iConst29) & 2047)];
			float fRec24 = (0.0f - (0.600000024f * fTemp31));
			float fTemp32 = (fRec23[1] + fRec24);
			float fTemp33 = (fRec21 + (fRec20[1] + fTemp32));
			fRec2[0] = (fRec7 + (fRec6[1] + (fRec18 + (fRec17[1] + fTemp33))));
			fRec3[0] = ((fRec7 + (fRec6[1] + (fRec17[1] + fRec18))) - fTemp33);
			float fTemp34 = (fRec20[1] + fRec21);
			fRec4[0] = ((fRec7 + (fRec6[1] + fTemp34)) - (fRec18 + (fRec17[1] + fTemp32)));
			fRec5[0] = ((fRec7 + (fRec6[1] + fTemp32)) - (fRec18 + (fRec17[1] + fTemp34)));
			float fTemp35 = (fConst5 * ((fConst6 * fRec1[2]) + (fConst30 * fRec1[1])));
			fRec1[0] = ((0.370000005f * (fRec3[0] + fRec4[0])) - fTemp35);
			fRec0[0] = ((fTemp35 + fRec1[0]) - (fConst34 * ((fConst35 * fRec0[2]) + (fConst36 * fRec0[1]))));
			float fTemp36 = (fConst5 * ((fConst6 * fRec27[2]) + (fConst30 * fRec27[1])));
			fRec27[0] = ((0.370000005f * (fRec3[0] - fRec4[0])) - fTemp36);
			fRec26[0] = ((fTemp36 + fRec27[0]) - (fConst34 * ((fConst35 * fRec26[2]) + (fConst36 * fRec26[1]))));
			output0[i] = FAUSTFLOAT(((fRec0[0] + fRec26[0]) + (fConst34 * ((fConst36 * (fRec0[1] + fRec26[1])) + (fConst35 * (fRec0[2] + fRec26[2]))))));
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			IOTA = (IOTA + 1);
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec6[1] = fRec6[0];
			fRec19[1] = fRec19[0];
			fRec17[1] = fRec17[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec25[1] = fRec25[0];
			fRec23[1] = fRec23[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			
		}
		
	}

	
};


#endif

#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// Random:
//---------------------------------------------------------------------
: r
: r
: r
: r
: r
------------ RESULTS --------------------
{226}->[254]->[421]->[701]->[918]->|||

[226]->[254]->[421]->[701]->{831}->[918]->|||
[226]->[254]->[421]->{551}->[701]->[831]->[918]->|||
[226]->[254]->[421]->[551]->{606}->[701]->[831]->[918]->|||
[226]->[254]->[421]->[551]->[606]->[701]->[831]->[918]->{964}->|||
[226]->[254]->[421]->[551]->[606]->{622}->[701]->[831]->[918]->[964]->|||


//---------------------------------------------------------------------
// Insert:
//---------------------------------------------------------------------
: i
: 100
: i
: 200
: i
: 300
: i
: 400
: i
: 500
------------ RESULTS --------------------
{129}->[179]->[579]->[728]->[745]->|||

[100]->[129]->[179]->[579]->[728]->[745]->|||
[100]->[129]->[179]->{200}->[579]->[728]->[745]->|||
[100]->[129]->[179]->[200]->{300}->[579]->[728]->[745]->|||
[100]->[129]->[179]->[200]->[300]->{400}->[579]->[728]->[745]->|||
[100]->[129]->[179]->[200]->[300]->[400]->{500}->[579]->[728]->[745]->|||


//---------------------------------------------------------------------
// Delete:
//---------------------------------------------------------------------
: d
: n
: d
: d
: d
------------ RESULTS --------------------
{500}->[545]->[762]->[776]->[866]->|||

{545}->[762]->[776]->[866]->|||
[545]->{762}->[776]->[866]->|||
{545}->[776]->[866]->|||
{776}->[866]->|||
{866}->|||


//---------------------------------------------------------------------
// Search:
//---------------------------------------------------------------------
: s
: 291
: s
: 504
: s
: 207
: s
: 745
: s
: 507
------------ RESULTS --------------------
{207}->[291]->[504]->[507]->[745]->|||

[207]->{291}->[504]->[507]->[745]->|||
[207]->[291]->{504}->[507]->[745]->|||
{207}->[291]->[504]->[507]->[745]->|||
[207]->[291]->[504]->[507]->{745}->|||
[207]->[291]->[504]->{507}->[745]->|||


//---------------------------------------------------------------------
// Next:
//---------------------------------------------------------------------
: n
: n
: n
: n
: n
------------ RESULTS --------------------
{64}->[77]->[421]->[548]->[583]->|||

[64]->{77}->[421]->[548]->[583]->|||
[64]->[77]->{421}->[548]->[583]->|||
[64]->[77]->[421]->{548}->[583]->|||
[64]->[77]->[421]->[548]->{583}->|||
[64]->[77]->[421]->[548]->{583}->|||


//---------------------------------------------------------------------
// Previous:
//---------------------------------------------------------------------
: n
: n
: n
: n
: p
: p
: p
: p
: p
------------ RESULTS --------------------
{85}->[646]->[685]->[815]->[900]->|||

[85]->{646}->[685]->[815]->[900]->|||
[85]->[646]->{685}->[815]->[900]->|||
[85]->[646]->[685]->{815}->[900]->|||
[85]->[646]->[685]->[815]->{900}->|||

[85]->[646]->[685]->{815}->[900]->|||
[85]->[646]->{685}->[815]->[900]->|||
[85]->{646}->[685]->[815]->[900]->|||
{85}->[646]->[685]->[815]->[900]->|||
{85}->[646]->[685]->[815]->[900]->|||


//---------------------------------------------------------------------
// Home:
//---------------------------------------------------------------------
: n
: h
------------ RESULTS --------------------
{232}->[319]->[488]->[760]->[976]->|||

[232]->{319}->[488]->[760]->[976]->|||
{232}->[319]->[488]->[760]->[976]->|||

//---------------------------------------------------------------------
// End:
//---------------------------------------------------------------------
: e
------------ RESULTS --------------------
{309}->[469]->[656]->[806]->[889]->|||

[309]->[469]->[656]->[806]->{889}->|||


*/
#endif // Z_OUTPUT_H
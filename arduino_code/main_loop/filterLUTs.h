#ifndef FILTERLUTS_H
#define FILTERLUTS_H

// table of 256 exponentially distributed filter coefficients between 100 Hz and 15 kHz
const float lowPassLUT[256][5] = {
{	0.00005024	,	0.00010048	,	0.00005024	,	1.97985154	,	-0.98005251	}	,
{	0.00005224	,	0.00010447	,	0.00005224	,	1.97945332	,	-0.97966227	}	,
{	0.00005431	,	0.00010862	,	0.00005431	,	1.97904723	,	-0.97926448	}	,
{	0.00005647	,	0.00011294	,	0.00005647	,	1.97863312	,	-0.97885899	}	,
{	0.00005871	,	0.00011742	,	0.00005871	,	1.97821082	,	-0.97844566	}	,
{	0.00006104	,	0.00012208	,	0.00006104	,	1.97778018	,	-0.97802435	}	,
{	0.00006346	,	0.00012693	,	0.00006346	,	1.97734103	,	-0.97759489	}	,
{	0.00006598	,	0.00013197	,	0.00006598	,	1.97689320	,	-0.97715713	}	,
{	0.00006860	,	0.00013720	,	0.00006860	,	1.97643652	,	-0.97671093	}	,
{	0.00007132	,	0.00014265	,	0.00007132	,	1.97597082	,	-0.97625611	}	,
{	0.00007415	,	0.00014831	,	0.00007415	,	1.97549591	,	-0.97579253	}	,
{	0.00007710	,	0.00015419	,	0.00007710	,	1.97501162	,	-0.97532001	}	,
{	0.00008015	,	0.00016031	,	0.00008015	,	1.97451777	,	-0.97483838	}	,
{	0.00008333	,	0.00016666	,	0.00008333	,	1.97401415	,	-0.97434748	}	,
{	0.00008664	,	0.00017327	,	0.00008664	,	1.97350058	,	-0.97384713	}	,
{	0.00009007	,	0.00018014	,	0.00009007	,	1.97297687	,	-0.97333715	}	,
{	0.00009364	,	0.00018729	,	0.00009364	,	1.97244280	,	-0.97281738	}	,
{	0.00009736	,	0.00019471	,	0.00009736	,	1.97189819	,	-0.97228761	}	,
{	0.00010121	,	0.00020243	,	0.00010121	,	1.97134281	,	-0.97174767	}	,
{	0.00010523	,	0.00021045	,	0.00010523	,	1.97077646	,	-0.97119736	}	,
{	0.00010939	,	0.00021879	,	0.00010939	,	1.97019892	,	-0.97063650	}	,
{	0.00011373	,	0.00022746	,	0.00011373	,	1.96960997	,	-0.97006489	}	,
{	0.00011823	,	0.00023647	,	0.00011823	,	1.96900939	,	-0.96948232	}	,
{	0.00012292	,	0.00024583	,	0.00012292	,	1.96839694	,	-0.96888861	}	,
{	0.00012778	,	0.00025557	,	0.00012778	,	1.96777239	,	-0.96828353	}	,
{	0.00013284	,	0.00026569	,	0.00013284	,	1.96713550	,	-0.96766688	}	,
{	0.00013810	,	0.00027621	,	0.00013810	,	1.96648603	,	-0.96703844	}	,
{	0.00014357	,	0.00028714	,	0.00014357	,	1.96582373	,	-0.96639801	}	,
{	0.00014925	,	0.00029850	,	0.00014925	,	1.96514834	,	-0.96574535	}	,
{	0.00015516	,	0.00031031	,	0.00015516	,	1.96445962	,	-0.96508025	}	,
{	0.00016129	,	0.00032259	,	0.00016129	,	1.96375729	,	-0.96440247	}	,
{	0.00016767	,	0.00033535	,	0.00016767	,	1.96304108	,	-0.96371178	}	,
{	0.00017431	,	0.00034861	,	0.00017431	,	1.96231073	,	-0.96300796	}	,
{	0.00018120	,	0.00036240	,	0.00018120	,	1.96156596	,	-0.96229075	}	,
{	0.00018836	,	0.00037672	,	0.00018836	,	1.96080647	,	-0.96155991	}	,
{	0.00019581	,	0.00039161	,	0.00019581	,	1.96003198	,	-0.96081520	}	,
{	0.00020354	,	0.00040709	,	0.00020354	,	1.95924220	,	-0.96005637	}	,
{	0.00021159	,	0.00042317	,	0.00021159	,	1.95843681	,	-0.95928315	}	,
{	0.00021994	,	0.00043989	,	0.00021994	,	1.95761552	,	-0.95849530	}	,
{	0.00022863	,	0.00045726	,	0.00022863	,	1.95677802	,	-0.95769253	}	,
{	0.00023766	,	0.00047531	,	0.00023766	,	1.95592397	,	-0.95687459	}	,
{	0.00024704	,	0.00049408	,	0.00024704	,	1.95505306	,	-0.95604121	}	,
{	0.00025679	,	0.00051358	,	0.00025679	,	1.95416495	,	-0.95519210	}	,
{	0.00026692	,	0.00053384	,	0.00026692	,	1.95325930	,	-0.95432698	}	,
{	0.00027745	,	0.00055490	,	0.00027745	,	1.95233577	,	-0.95344557	}	,
{	0.00028839	,	0.00057678	,	0.00028839	,	1.95139401	,	-0.95254758	}	,
{	0.00029976	,	0.00059953	,	0.00029976	,	1.95043365	,	-0.95163270	}	,
{	0.00031158	,	0.00062316	,	0.00031158	,	1.94945433	,	-0.95070065	}	,
{	0.00032386	,	0.00064772	,	0.00032386	,	1.94845568	,	-0.94975112	}	,
{	0.00033662	,	0.00067324	,	0.00033662	,	1.94743731	,	-0.94878380	}	,
{	0.00034988	,	0.00069976	,	0.00034988	,	1.94639885	,	-0.94779837	}	,
{	0.00036366	,	0.00072732	,	0.00036366	,	1.94533988	,	-0.94679452	}	,
{	0.00037798	,	0.00075595	,	0.00037798	,	1.94426001	,	-0.94577192	}	,
{	0.00039285	,	0.00078571	,	0.00039285	,	1.94315883	,	-0.94473024	}	,
{	0.00040831	,	0.00081662	,	0.00040831	,	1.94203591	,	-0.94366916	}	,
{	0.00042437	,	0.00084875	,	0.00042437	,	1.94089084	,	-0.94258834	}	,
{	0.00044106	,	0.00088213	,	0.00044106	,	1.93972317	,	-0.94148742	}	,
{	0.00045840	,	0.00091681	,	0.00045840	,	1.93853245	,	-0.94036607	}	,
{	0.00047642	,	0.00095284	,	0.00047642	,	1.93731825	,	-0.93922393	}	,
{	0.00049514	,	0.00099028	,	0.00049514	,	1.93608008	,	-0.93806064	}	,
{	0.00051459	,	0.00102918	,	0.00051459	,	1.93481749	,	-0.93687585	}	,
{	0.00053479	,	0.00106959	,	0.00053479	,	1.93352999	,	-0.93566917	}	,
{	0.00055579	,	0.00111158	,	0.00055579	,	1.93221710	,	-0.93444025	}	,
{	0.00057760	,	0.00115519	,	0.00057760	,	1.93087831	,	-0.93318870	}	,
{	0.00060026	,	0.00120051	,	0.00060026	,	1.92951312	,	-0.93191414	}	,
{	0.00062379	,	0.00124759	,	0.00062379	,	1.92812100	,	-0.93061617	}	,
{	0.00064825	,	0.00129649	,	0.00064825	,	1.92670143	,	-0.92929442	}	,
{	0.00067365	,	0.00134730	,	0.00067365	,	1.92525387	,	-0.92794847	}	,
{	0.00070004	,	0.00140008	,	0.00070004	,	1.92377777	,	-0.92657793	}	,
{	0.00072745	,	0.00145490	,	0.00072745	,	1.92227258	,	-0.92518238	}	,
{	0.00075593	,	0.00151185	,	0.00075593	,	1.92073771	,	-0.92376142	}	,
{	0.00078551	,	0.00157101	,	0.00078551	,	1.91917259	,	-0.92231461	}	,
{	0.00081623	,	0.00163246	,	0.00081623	,	1.91757662	,	-0.92084154	}	,
{	0.00084814	,	0.00169629	,	0.00084814	,	1.91594921	,	-0.91934178	}	,
{	0.00088129	,	0.00176258	,	0.00088129	,	1.91428973	,	-0.91781489	}	,
{	0.00091572	,	0.00183144	,	0.00091572	,	1.91259756	,	-0.91626043	}	,
{	0.00095148	,	0.00190296	,	0.00095148	,	1.91087205	,	-0.91467796	}	,
{	0.00098862	,	0.00197723	,	0.00098862	,	1.90911256	,	-0.91306703	}	,
{	0.00102719	,	0.00205438	,	0.00102719	,	1.90731842	,	-0.91142717	}	,
{	0.00106725	,	0.00213450	,	0.00106725	,	1.90548895	,	-0.90975794	}	,
{	0.00110885	,	0.00221770	,	0.00110885	,	1.90362346	,	-0.90805886	}	,
{	0.00115206	,	0.00230411	,	0.00115206	,	1.90172125	,	-0.90632947	}	,
{	0.00119692	,	0.00239384	,	0.00119692	,	1.89978160	,	-0.90456929	}	,
{	0.00124351	,	0.00248703	,	0.00124351	,	1.89780378	,	-0.90277783	}	,
{	0.00129190	,	0.00258379	,	0.00129190	,	1.89578704	,	-0.90095463	}	,
{	0.00134213	,	0.00268427	,	0.00134213	,	1.89373064	,	-0.89909917	}	,
{	0.00139430	,	0.00278860	,	0.00139430	,	1.89163378	,	-0.89721098	}	,
{	0.00144847	,	0.00289694	,	0.00144847	,	1.88949568	,	-0.89528956	}	,
{	0.00150471	,	0.00300942	,	0.00150471	,	1.88731555	,	-0.89333439	}	,
{	0.00156310	,	0.00312620	,	0.00156310	,	1.88509256	,	-0.89134497	}	,
{	0.00162373	,	0.00324746	,	0.00162373	,	1.88282589	,	-0.88932080	}	,
{	0.00168667	,	0.00337334	,	0.00168667	,	1.88051467	,	-0.88726135	}	,
{	0.00175202	,	0.00350404	,	0.00175202	,	1.87815804	,	-0.88516611	}	,
{	0.00181986	,	0.00363971	,	0.00181986	,	1.87575513	,	-0.88303455	}	,
{	0.00189028	,	0.00378056	,	0.00189028	,	1.87330503	,	-0.88086615	}	,
{	0.00196339	,	0.00392677	,	0.00196339	,	1.87080683	,	-0.87866037	}	,
{	0.00203927	,	0.00407855	,	0.00203927	,	1.86825959	,	-0.87641669	}	,
{	0.00211804	,	0.00423609	,	0.00211804	,	1.86566238	,	-0.87413456	}	,
{	0.00219981	,	0.00439961	,	0.00219981	,	1.86301421	,	-0.87181344	}	,
{	0.00228467	,	0.00456934	,	0.00228467	,	1.86031411	,	-0.86945279	}	,
{	0.00237275	,	0.00474550	,	0.00237275	,	1.85756107	,	-0.86705207	}	,
{	0.00246416	,	0.00492833	,	0.00246416	,	1.85475406	,	-0.86461072	}	,
{	0.00255904	,	0.00511807	,	0.00255904	,	1.85189206	,	-0.86212821	}	,
{	0.00265749	,	0.00531499	,	0.00265749	,	1.84897399	,	-0.85960396	}	,
{	0.00275967	,	0.00551933	,	0.00275967	,	1.84599878	,	-0.85703744	}	,
{	0.00286569	,	0.00573138	,	0.00286569	,	1.84296532	,	-0.85442809	}	,
{	0.00297571	,	0.00595142	,	0.00297571	,	1.83987250	,	-0.85177535	}	,
{	0.00308987	,	0.00617973	,	0.00308987	,	1.83671918	,	-0.84907865	}	,
{	0.00320831	,	0.00641663	,	0.00320831	,	1.83350420	,	-0.84633746	}	,
{	0.00333121	,	0.00666241	,	0.00333121	,	1.83022637	,	-0.84355120	}	,
{	0.00345871	,	0.00691741	,	0.00345871	,	1.82688449	,	-0.84071932	}	,
{	0.00359098	,	0.00718196	,	0.00359098	,	1.82347734	,	-0.83784126	}	,
{	0.00372820	,	0.00745641	,	0.00372820	,	1.82000366	,	-0.83491648	}	,
{	0.00387055	,	0.00774110	,	0.00387055	,	1.81646220	,	-0.83194440	}	,
{	0.00401821	,	0.00803642	,	0.00401821	,	1.81285165	,	-0.82892448	}	,
{	0.00417137	,	0.00834274	,	0.00417137	,	1.80917070	,	-0.82585617	}	,
{	0.00433023	,	0.00866045	,	0.00433023	,	1.80541801	,	-0.82273892	}	,
{	0.00449499	,	0.00898998	,	0.00449499	,	1.80159223	,	-0.81957219	}	,
{	0.00466587	,	0.00933173	,	0.00466587	,	1.79769195	,	-0.81635542	}	,
{	0.00484308	,	0.00968615	,	0.00484308	,	1.79371578	,	-0.81308809	}	,
{	0.00502685	,	0.01005369	,	0.00502685	,	1.78966228	,	-0.80976966	}	,
{	0.00521741	,	0.01043481	,	0.00521741	,	1.78552998	,	-0.80639961	}	,
{	0.00541500	,	0.01083000	,	0.00541500	,	1.78131741	,	-0.80297740	}	,
{	0.00561987	,	0.01123974	,	0.00561987	,	1.77702305	,	-0.79950253	}	,
{	0.00583228	,	0.01166457	,	0.00583228	,	1.77264535	,	-0.79597449	}	,
{	0.00605250	,	0.01210500	,	0.00605250	,	1.76818277	,	-0.79239277	}	,
{	0.00628079	,	0.01256159	,	0.00628079	,	1.76363370	,	-0.78875687	}	,
{	0.00651745	,	0.01303489	,	0.00651745	,	1.75899653	,	-0.78506632	}	,
{	0.00676276	,	0.01352551	,	0.00676276	,	1.75426962	,	-0.78132064	}	,
{	0.00701702	,	0.01403404	,	0.00701702	,	1.74945129	,	-0.77751936	}	,
{	0.00728055	,	0.01456110	,	0.00728055	,	1.74453984	,	-0.77366203	}	,
{	0.00755367	,	0.01510733	,	0.00755367	,	1.73953355	,	-0.76974821	}	,
{	0.00783670	,	0.01567341	,	0.00783670	,	1.73443065	,	-0.76577747	}	,
{	0.00813001	,	0.01626001	,	0.00813001	,	1.72922936	,	-0.76174938	}	,
{	0.00843392	,	0.01686785	,	0.00843392	,	1.72392786	,	-0.75766355	}	,
{	0.00874882	,	0.01749764	,	0.00874882	,	1.71852431	,	-0.75351960	}	,
{	0.00907508	,	0.01815015	,	0.00907508	,	1.71301683	,	-0.74931714	}	,
{	0.00941308	,	0.01882615	,	0.00941308	,	1.70740353	,	-0.74505583	}	,
{	0.00976322	,	0.01952644	,	0.00976322	,	1.70168245	,	-0.74073533	}	,
{	0.01012592	,	0.02025184	,	0.01012592	,	1.69585164	,	-0.73635532	}	,
{	0.01050160	,	0.02100321	,	0.01050160	,	1.68990909	,	-0.73191551	}	,
{	0.01089071	,	0.02178141	,	0.01089071	,	1.68385279	,	-0.72741561	}	,
{	0.01129368	,	0.02258736	,	0.01129368	,	1.67768066	,	-0.72285538	}	,
{	0.01171099	,	0.02342198	,	0.01171099	,	1.67139062	,	-0.71823459	}	,
{	0.01214312	,	0.02428624	,	0.01214312	,	1.66498054	,	-0.71355301	}	,
{	0.01259056	,	0.02518112	,	0.01259056	,	1.65844826	,	-0.70881049	}	,
{	0.01305381	,	0.02610763	,	0.01305381	,	1.65179159	,	-0.70400685	}	,
{	0.01353341	,	0.02706683	,	0.01353341	,	1.64500832	,	-0.69914198	}	,
{	0.01402990	,	0.02805980	,	0.01402990	,	1.63809618	,	-0.69421578	}	,
{	0.01454382	,	0.02908764	,	0.01454382	,	1.63105289	,	-0.68922817	}	,
{	0.01507575	,	0.03015150	,	0.01507575	,	1.62387613	,	-0.68417912	}	,
{	0.01562628	,	0.03125256	,	0.01562628	,	1.61656352	,	-0.67906864	}	,
{	0.01619601	,	0.03239203	,	0.01619601	,	1.60911269	,	-0.67389675	}	,
{	0.01678558	,	0.03357115	,	0.01678558	,	1.60152121	,	-0.66866352	}	,
{	0.01739561	,	0.03479121	,	0.01739561	,	1.59378662	,	-0.66336905	}	,
{	0.01802677	,	0.03605353	,	0.01802677	,	1.58590643	,	-0.65801349	}	,
{	0.01867973	,	0.03735947	,	0.01867973	,	1.57787810	,	-0.65259703	}	,
{	0.01935520	,	0.03871041	,	0.01935520	,	1.56969906	,	-0.64711988	}	,
{	0.02005390	,	0.04010780	,	0.02005390	,	1.56136673	,	-0.64158232	}	,
{	0.02077655	,	0.04155310	,	0.02077655	,	1.55287846	,	-0.63598467	}	,
{	0.02152392	,	0.04304785	,	0.02152392	,	1.54423157	,	-0.63032727	}	,
{	0.02229679	,	0.04459359	,	0.02229679	,	1.53542337	,	-0.62461054	}	,
{	0.02309596	,	0.04619192	,	0.02309596	,	1.52645111	,	-0.61883495	}	,
{	0.02392225	,	0.04784449	,	0.02392225	,	1.51731200	,	-0.61300099	}	,
{	0.02477650	,	0.04955300	,	0.02477650	,	1.50800324	,	-0.60710923	}	,
{	0.02565958	,	0.05131917	,	0.02565958	,	1.49852195	,	-0.60116029	}	,
{	0.02657240	,	0.05314479	,	0.02657240	,	1.48886526	,	-0.59515484	}	,
{	0.02751585	,	0.05503169	,	0.02751585	,	1.47903023	,	-0.58909362	}	,
{	0.02849088	,	0.05698176	,	0.02849088	,	1.46901390	,	-0.58297742	}	,
{	0.02949846	,	0.05899692	,	0.02949846	,	1.45881326	,	-0.57680709	}	,
{	0.03053957	,	0.06107914	,	0.03053957	,	1.44842527	,	-0.57058356	}	,
{	0.03161524	,	0.06323048	,	0.03161524	,	1.43784685	,	-0.56430781	}	,
{	0.03272651	,	0.06545301	,	0.03272651	,	1.42707487	,	-0.55798090	}	,
{	0.03387444	,	0.06774888	,	0.03387444	,	1.41610619	,	-0.55160394	}	,
{	0.03506014	,	0.07012028	,	0.03506014	,	1.40493759	,	-0.54517814	}	,
{	0.03628473	,	0.07256946	,	0.03628473	,	1.39356584	,	-0.53870476	}	,
{	0.03754937	,	0.07509875	,	0.03754937	,	1.38198766	,	-0.53218516	}	,
{	0.03885525	,	0.07771051	,	0.03885525	,	1.37019973	,	-0.52562075	}	,
{	0.04020359	,	0.08040717	,	0.04020359	,	1.35819869	,	-0.51901304	}	,
{	0.04159562	,	0.08319124	,	0.04159562	,	1.34598113	,	-0.51236361	}	,
{	0.04303264	,	0.08606527	,	0.04303264	,	1.33354361	,	-0.50567415	}	,
{	0.04451594	,	0.08903189	,	0.04451594	,	1.32088264	,	-0.49894641	}	,
{	0.04604689	,	0.09209378	,	0.04604689	,	1.30799467	,	-0.49218224	}	,
{	0.04762686	,	0.09525372	,	0.04762686	,	1.29487614	,	-0.48538357	}	,
{	0.04925726	,	0.09851452	,	0.04925726	,	1.28152341	,	-0.47855245	}	,
{	0.05093955	,	0.10187910	,	0.05093955	,	1.26793281	,	-0.47169100	}	,
{	0.05267521	,	0.10535042	,	0.05267521	,	1.25410062	,	-0.46480146	}	,
{	0.05446577	,	0.10893155	,	0.05446577	,	1.24002306	,	-0.45788616	}	,
{	0.05631280	,	0.11262560	,	0.05631280	,	1.22569632	,	-0.45094752	}	,
{	0.05821790	,	0.11643580	,	0.05821790	,	1.21111652	,	-0.44398811	}	,
{	0.06018271	,	0.12036542	,	0.06018271	,	1.19627973	,	-0.43701057	}	,
{	0.06220893	,	0.12441786	,	0.06220893	,	1.18118195	,	-0.43001767	}	,
{	0.06429828	,	0.12859656	,	0.06429828	,	1.16581915	,	-0.42301228	}	,
{	0.06645255	,	0.13290510	,	0.06645255	,	1.15018722	,	-0.41599741	}	,
{	0.06867355	,	0.13734710	,	0.06867355	,	1.13428199	,	-0.40897619	}	,
{	0.07096316	,	0.14192632	,	0.07096316	,	1.11809922	,	-0.40195186	}	,
{	0.07332329	,	0.14664659	,	0.07332329	,	1.10163462	,	-0.39492780	}	,
{	0.07575593	,	0.15151186	,	0.07575593	,	1.08488381	,	-0.38790752	}	,
{	0.07826308	,	0.15652617	,	0.07826308	,	1.06784233	,	-0.38089466	}	,
{	0.08084684	,	0.16169368	,	0.08084684	,	1.05050566	,	-0.37389302	}	,
{	0.08350933	,	0.16701867	,	0.08350933	,	1.03286919	,	-0.36690653	}	,
{	0.08625276	,	0.17250552	,	0.08625276	,	1.01492821	,	-0.35993926	}	,
{	0.08907938	,	0.17815875	,	0.08907938	,	0.99667794	,	-0.35299545	}	,
{	0.09199150	,	0.18398301	,	0.09199150	,	0.97811349	,	-0.34607950	}	,
{	0.09499153	,	0.18998306	,	0.09499153	,	0.95922986	,	-0.33919597	}	,
{	0.09808191	,	0.19616382	,	0.09808191	,	0.94002195	,	-0.33234959	}	,
{	0.10126517	,	0.20253035	,	0.10126517	,	0.92048456	,	-0.32554526	}	,
{	0.10454393	,	0.20908787	,	0.10454393	,	0.90061234	,	-0.31878807	}	,
{	0.10792087	,	0.21584174	,	0.10792087	,	0.88039982	,	-0.31208331	}	,
{	0.11139876	,	0.22279752	,	0.11139876	,	0.85984141	,	-0.30543644	}	,
{	0.11498046	,	0.22996091	,	0.11498046	,	0.83893134	,	-0.29885317	}	,
{	0.11866891	,	0.23733783	,	0.11866891	,	0.81766372	,	-0.29233938	}	,
{	0.12246718	,	0.24493437	,	0.12246718	,	0.79603247	,	-0.28590120	}	,
{	0.12637841	,	0.25275683	,	0.12637841	,	0.77403133	,	-0.27954498	}	,
{	0.13040587	,	0.26081173	,	0.13040587	,	0.75165388	,	-0.27327734	}	,
{	0.13455292	,	0.26910584	,	0.13455292	,	0.72889347	,	-0.26710514	}	,
{	0.13882307	,	0.27764613	,	0.13882307	,	0.70574325	,	-0.26103551	}	,
{	0.14321994	,	0.28643987	,	0.14321994	,	0.68219613	,	-0.25507588	}	,
{	0.14774729	,	0.29549459	,	0.14774729	,	0.65824479	,	-0.24923396	}	,
{	0.15240904	,	0.30481809	,	0.15240904	,	0.63388164	,	-0.24351781	}	,
{	0.15720925	,	0.31441850	,	0.15720925	,	0.60909881	,	-0.23793580	}	,
{	0.16215213	,	0.32430427	,	0.16215213	,	0.58388814	,	-0.23249668	}	,
{	0.16724210	,	0.33448421	,	0.16724210	,	0.55824114	,	-0.22720956	}	,
{	0.17248374	,	0.34496749	,	0.17248374	,	0.53214900	,	-0.22208397	}	,
{	0.17788184	,	0.35576368	,	0.17788184	,	0.50560252	,	-0.21712988	}	,
{	0.18344140	,	0.36688279	,	0.18344140	,	0.47859212	,	-0.21235770	}	,
{	0.18916763	,	0.37833527	,	0.18916763	,	0.45110782	,	-0.20777835	}	,
{	0.19506603	,	0.39013205	,	0.19506603	,	0.42313917	,	-0.20340327	}	,
{	0.20114231	,	0.40228461	,	0.20114231	,	0.39467527	,	-0.19924449	}	,
{	0.20740248	,	0.41480497	,	0.20740248	,	0.36570468	,	-0.19531462	}	,
{	0.21385288	,	0.42770575	,	0.21385288	,	0.33621545	,	-0.19162695	}	,
{	0.22050012	,	0.44100024	,	0.22050012	,	0.30619502	,	-0.18819549	}	,
{	0.22735119	,	0.45470239	,	0.22735119	,	0.27563022	,	-0.18503499	}	,
{	0.23441346	,	0.46882693	,	0.23441346	,	0.24450722	,	-0.18216107	}	,
{	0.24169469	,	0.48338938	,	0.24169469	,	0.21281146	,	-0.17959023	}	,
{	0.24920308	,	0.49840616	,	0.24920308	,	0.18052763	,	-0.17733995	}	,
{	0.25694730	,	0.51389459	,	0.25694730	,	0.14763960	,	-0.17542879	}	,
{	0.26493652	,	0.52987305	,	0.26493652	,	0.11413037	,	-0.17387646	}	,
{	0.27318049	,	0.54636098	,	0.27318049	,	0.07998201	,	-0.17270396	}	,
{	0.28168952	,	0.56337905	,	0.28168952	,	0.04517558	,	-0.17193367	}	,
{	0.29047460	,	0.58094920	,	0.29047460	,	0.00969108	,	-0.17158948	}	,
{	0.29954739	,	0.59909478	,	0.29954739	,	-0.02649262	,	-0.17169695	}	,
{	0.30892034	,	0.61784068	,	0.30892034	,	-0.06339788	,	-0.17228348	}	,
{	0.31860671	,	0.63721342	,	0.31860671	,	-0.10104837	,	-0.17337848	}	,
{	0.32862068	,	0.65724135	,	0.32862068	,	-0.13946914	,	-0.17501356	}	,
{	0.33897738	,	0.67795476	,	0.33897738	,	-0.17868671	,	-0.17722281	}	,
{	0.34969306	,	0.69938611	,	0.34969306	,	-0.21872923	,	-0.18004299	}	,
{	0.36078509	,	0.72157018	,	0.36078509	,	-0.25962649	,	-0.18351388	}	,
{	0.37227217	,	0.74454433	,	0.37227217	,	-0.30141011	,	-0.18767855	}	,
{	0.38417435	,	0.76834870	,	0.38417435	,	-0.34411362	,	-0.19258378	}	,
{	0.39651325	,	0.79302651	,	0.39651325	,	-0.38777256	,	-0.19828045	}	,
{	0.40931216	,	0.81862433	,	0.40931216	,	-0.43242466	,	-0.20482399	}	,
{	0.42259622	,	0.84519243	,	0.42259622	,	-0.47810991	,	-0.21227496	}	,
{	0.43639258	,	0.87278515	,	0.43639258	,	-0.52487071	,	-0.22069960	}	,
{	0.45073064	,	0.90146128	,	0.45073064	,	-0.57275200	,	-0.23017056	}	,
{	0.46564226	,	0.93128451	,	0.46564226	,	-0.62180136	,	-0.24076767	}	
};

#endif

--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.8
-- Dumped by pg_dump version 9.5.8

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: jobber; Type: COMMENT; Schema: -; Owner: andersbo
--

COMMENT ON DATABASE jobber IS 'En liten database med oversikt over ulike jobber, inkl hvor de er, søknadsfrister, statuser, etc.';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: nylandid(); Type: FUNCTION; Schema: public; Owner: andersbo
--

CREATE FUNCTION nylandid() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
RAISE NOTICE 'Landet % med ID % ble lagt inn i databasen.', NEW.land, NEW.landid;
RETURN NEW;
END;
$$;


ALTER FUNCTION public.nylandid() OWNER TO andersbo;

--
-- Name: nysoknadid(); Type: FUNCTION; Schema: public; Owner: andersbo
--

CREATE FUNCTION nysoknadid() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
RAISE NOTICE
'Søknad med ID % ble lagt inn i databasen.', NEW.soknadid;
RETURN NEW;
END;
$$;


ALTER FUNCTION public.nysoknadid() OWNER TO andersbo;

--
-- Name: nystedid(); Type: FUNCTION; Schema: public; Owner: andersbo
--

CREATE FUNCTION nystedid() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
RAISE NOTICE 'Sted % med ID % ble lagt inn i databasen.', NEW.stedsnavn, NEW.stedid;
RETURN NEW;
END;
$$;


ALTER FUNCTION public.nystedid() OWNER TO andersbo;

--
-- Name: updatesoknad(); Type: FUNCTION; Schema: public; Owner: andersbo
--

CREATE FUNCTION updatesoknad() RETURNS trigger
    LANGUAGE plpgsql
    AS $$DECLARE
counter_ integer := 0;
tablename_ text := 'temptable';
oldStatus text;
newStatus text;
max int;
updated boolean := false;
BEGIN
 begin
        --raise notice 'Creating table %', tablename_;
        execute 'create temporary table ' || tablename_ || ' (counter integer) on commit drop';
        execute 'insert into ' || tablename_ || ' (counter) values(0)';
        execute 'select counter from ' || tablename_ into counter_;
        --raise notice 'Actual value for counter= [%]', counter_;
    exception
        when duplicate_table then
        null;
    end;


execute 'select counter from ' || tablename_ into counter_;
    execute 'update ' || tablename_ || ' set counter = counter + 1';
   --raise notice 'updating';
    execute 'select counter from ' || tablename_ into counter_;
    --raise notice 'Actual value for counter= [%]', counter_;
    max := count(soknadid) from soknad;
    if counter_ = max then
        raise exception 'Kan ikke oppdatere mer enn én rad om gangen.';
    end if;
if NEW.soknadid != OLD.soknadid
then
raise notice 'Søknadid-en ble endret fra % til %.', OLD.soknadid, NEW.soknadid;
updated = true;
end if;
if NEW.tittel != OLD.tittel
then
raise notice 'Søknaden med ID % har fått endret tittel fra % til %.', OLD.soknadid, OLD.tittel, NEW.tittel;
updated=true;
end if;

if NEW.bedrift != OLD.bedrift
then
raise notice 'Søknaden med ID % har fått endret bedrift fra % til %.', OLD.soknadid, OLD.bedrift, NEW.bedrift;

updated=true;
end if;

if NEW.stedid != OLD.stedid
then
raise notice 'Søknaden med ID % har fått endret stedid fra % til %.', OLD.soknadid, OLD.stedid, NEW.stedid;
updated=true;
end if;

if NEW.soknadsfrist != OLD.soknadsfrist
then
raise notice 'Søknaden med ID % har fått endret søknadsfrist fra % til %.', OLD.soknadid, OLD.soknadsfrist, NEW.soknadsfrist;
updated = true;
end if;


if NEW.statusid != OLD.statusid
then
if OLD.statusid = 1
then
oldStatus = 'Registrert';
elsif OLD.statusid = 2
then
oldStatus = 'Sendt';
elsif OLD.statusid = 3
then
oldStatus = 'Interessert, mulig intervju';
elsif OLD.statusid = 4
then
oldStatus = 'Avvist';
elsif OLD.statusid = 5
then
oldStatus = 'Søknad skrevet, men ikke sendt';
elsif OLD.statusid = 6
then
oldStatus = 'Godtatt, klar for jobb';
end if;
if NEW.statusid = 1
then
newStatus = 'Registrert';
elsif NEW.statusid = 2
then
newStatus = 'Sendt';
elsif NEW.statusid = 3
then
newStatus = 'Interessert, mulig intervju';
elsif NEW.statusid = 4
then
newStatus = 'Avvist';
elsif NEW.statusid = 5
then
newStatus = 'Søknad skrevet, men ikke sendt';
elsif NEW.statusid = 6
then
newStatus = 'Godtatt, klar for jobb';
end if;
raise notice 'Søknaden med ID % har fått endret statusid fra % (%) til % (%).', OLD.soknadid, OLD.statusid, oldStatus, NEW.statusid, newStatus;
elsif NEW.statusid = OLD.statusid
then
if updated = false
then
if OLD.statusid = 1
then
oldStatus = 'Registrert';
elsif OLD.statusid = 2
then
oldStatus = 'Sendt';
elsif OLD.statusid = 3
then
oldStatus = 'Interessert, mulig intervju';
elsif OLD.statusid = 4
then
oldStatus = 'Avvist';
elsif OLD.statusid = 5
then
oldStatus = 'Søknad skrevet, men ikke sendt';
elsif OLD.statusid = 6
then
oldStatus = 'Godtatt, klar for jobb';
end if;
raise notice 'Søknaden med ID % har IKKE fått endret status. Statusen forblir % (%).', OLD.soknadid, OLD.statusid, oldStatus;
end if;
end if;
RETURN NEW;
END;

$$;


ALTER FUNCTION public.updatesoknad() OWNER TO andersbo;

--
-- Name: landid_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE landid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE landid_seq OWNER TO andersbo;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: land; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE land (
    landid integer DEFAULT nextval('landid_seq'::regclass) NOT NULL,
    land text NOT NULL
);


ALTER TABLE land OWNER TO andersbo;

--
-- Name: soknadid_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE soknadid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE soknadid_seq OWNER TO andersbo;

--
-- Name: soknad; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE soknad (
    soknadid integer DEFAULT nextval('soknadid_seq'::regclass) NOT NULL,
    tittel text NOT NULL,
    bedrift text NOT NULL,
    stedid integer NOT NULL,
    statusid integer NOT NULL,
    soknadsfrist text NOT NULL
);


ALTER TABLE soknad OWNER TO andersbo;

--
-- Name: statusid_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE statusid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE statusid_seq OWNER TO andersbo;

--
-- Name: status; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE status (
    statusid integer DEFAULT nextval('statusid_seq'::regclass) NOT NULL,
    status character varying(30) NOT NULL
);


ALTER TABLE status OWNER TO andersbo;

--
-- Name: stedid_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE stedid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE stedid_seq OWNER TO andersbo;

--
-- Name: sted; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE sted (
    stedid integer DEFAULT nextval('stedid_seq'::regclass) NOT NULL,
    stedsnavn text NOT NULL,
    landid integer NOT NULL
);


ALTER TABLE sted OWNER TO andersbo;

--
-- Name: user_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE user_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE user_id_seq OWNER TO andersbo;

--
-- Name: view_soknad; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW view_soknad AS
 SELECT soknad.soknadid,
    soknad.tittel,
    soknad.bedrift,
    soknad.soknadsfrist,
    soknad.stedid,
    sted.stedsnavn,
    sted.landid,
    land.land,
    soknad.statusid,
    status.status
   FROM (((soknad
     JOIN sted ON ((sted.stedid = soknad.stedid)))
     JOIN land ON ((land.landid = sted.landid)))
     JOIN status ON ((status.statusid = soknad.statusid)))
  ORDER BY soknad.soknadid;


ALTER TABLE view_soknad OWNER TO andersbo;

--
-- Name: view_sted; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW view_sted AS
 SELECT sted.stedid,
    sted.stedsnavn,
    sted.landid,
    land.land
   FROM (sted
     JOIN land ON ((land.landid = sted.landid)));


ALTER TABLE view_sted OWNER TO andersbo;

--
-- Data for Name: land; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY land (landid, land) FROM stdin;
1	Norge
2	Sverige
3	Danmark
\.


--
-- Name: landid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('landid_seq', 3, true);


--
-- Data for Name: soknad; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY soknad (soknadid, tittel, bedrift, stedid, statusid, soknadsfrist) FROM stdin;
3	Webbdesigner/Frontendutvecklare/Webbutvecklare	Trollweb Solutions AB	4	4	2016-09-08
4	IT-tekniker	Alina Systems i Östersund AB	4	2	2016-12-15
5	Systemutvecklare .NET	Combitech	4	4	2016-11-19
6	Front End utvecklare	Fogwise AB	4	1	2017-03-01
7	Databasutvecklare	Migrationsverket	4	2	2016-10-30
8	Systemutvecklare Java	Migrationsverket	4	4	2016-11-21
9	Systemutvecklare	Montico	4	2	2016-11-30
10	Applikationsutvecklare inriktning Integrationer	Sjöfartsverket	4	2	2016-11-27
11	Systemförvaltare Kontorsstöd	SMHI	4	2	2016-11-24
12	Butikssäljare 75 %	Stadium Norrköping	4	4	2016-11-13
13	Utvecklare/programmerare med inriktning mot 3D på webben	SWECO AB	4	4	2016-10-30
14	Utvikler	NAF	2	4	2016-11-14
16	Product Coordinator	Stadium Norrköping	4	4	2016-12-13
15	.NET C# Systemutvecklare	Teknomedia	4	4	2016-12-31
17	Fälttekniker, Norrköping	Barona Human Resource Services AB	4	2	2016-12-31
18	Testutveckling inom Mjukvara	i3tex AB	4	4	2016-12-20
19	Servicetekniker	SFT Bredbandsgruppen AB	4	2	2016-12-23
20	Helpdeskmedarbetare med servicekänsla	Perido	4	2	2016-12-29
21	Systemarkitekt	JobBusters AB	4	4	2017-01-30
22	.NET-utvecklare	Revide (via Academic Work)	4	4	2017-01-09
23	Webbutvecklare	TaxiCaller Nordic AB	5	2	2017-01-10
24	.NET-utvecklare	Consid	4	2	2017-01-14
25	JAVA-utvecklare Norrköping	Cybercom Group AB	4	4	2017-01-15
26	Driven supportspecialist med brinnande kundfokus	Industrikompetens i Östergötland AB	4	2	2017-01-31
27	Full Stack Developer	Prevas	4	2	2017-01-31
28	Junior .NET utvikler	Rett Bemanning Oslo Vest	2	4	2017-01-15
29	Junior Applikationsutvecklare	Apetan	5	2	2017-01-20
30	Java-utvecklare Norrköping	Consid	4	2	2017-02-10
31	Vetenskapsprogrammerare med goda systemutvecklingskunskaper	SMHI	4	4	2017-01-29
32	Webbutvecklare	Compriser AB	4	2	2017-01-31
33	.NET-utviklere	Lånekassen	2	2	2017-01-23
34	Systemutvecklare	i3tex	4	2	2017-02-12
35	Webbutvecklare	i3tex	4	4	2017-02-12
37	Norsktalande supporttekniker i Linköping	Dfind IT	5	4	2017-01.31
38	Junior frontend-utvecklare	Nethouse via Academic Work	5	4	2017-03-07
39	Webbutvecklare/Applikationsutvecklare	Ventiro AB	4	4	2017-02-28
40	Systemutvecklare till inhouseverksamhet	Framtiden AB	4	2	2017-03-22
41	Junior mjukvaruutvecklare	Etteplan Industry AB	5	2	2017-03-12
43	Mjukvaruutvecklare med genuint teknikintresse	SysPartner via Xamera	5	2	2017-04-22
44	Utvecklare	Millenway Development AB	4	2	2017-02-28
45	Systemutvecklare	XLENT	4	4	2017-03-09
48	Softwareutvikler	Hiddn Security AS	2	2	2017-04-06
49	Nyexaminerade mjukvaruutvecklare	Alten Sverige AB	5	4	2017-04-27
50	Mjukvaruutvecklare	Ides AB via Xamera	5	1	2017-06-07
52	.NET/C# utvecklare i Norrköping	HiQ Accelerated Concept Evaluation AB	4	4	2017-04-23
54	Junior .NET-utvecklare Norrköping	Consid	4	1	2017-05-15
55	Systemutvikler	NettPost AS (Bærum)	2	2	2017-04-30
57	Junior C#/.NET-utvecklare	Arenius Schröder & Besterman Talents AB	5	4	2017-04-28
58	System Developer	E2U Systems	9	2	Snarest
36	Systemutvecklare .NET till inhouseverksamhet i Norrköping	Combitech	4	2	2017-05-31
47	Utvikler	eSmart Systems	7	4	Snarest
53	Systemutvecklare/Programmerare	InspireIT	4	2	2017-05-10
76	Junior programmerare till framtida uppdrag	StudentConsulting	3	4	2017-06-30
46	Systemutvecklare till Holmen	Academic Work	4	2	2017-04-20
61	Systemutvikler	Oslo Universitetssykehus	2	2	2017-05-21
62	Systemutvikler	Kredinor via Academic Work	2	3	2017-05-18
64	Junior Full Stack Developer	Framtiden AB	5	2	2017-05-27
65	Juniora systemutvecklare	Netgain via Framtiden	4	2	2017-05-13
51	Softwareutvikler	Prediktor AS	9	4	2017-05-14
66	Webbutvecklare	Svenskalag.se	4	2	2017-06-01
42	Testare (mjukvara) och testansvarig i Linköping	Avenda Solutions AB	5	1	2017-03-14
60	Briljant systemutvecklare	Briljant (via Academic Work)	4	4	2017-06-02
70	Backendutvecklare sökes till Linköping	Framtiden AB	5	2	2017-06-30
59	Systemutvecklare	Combitech AB	5	2	2017-05-28
69	Webutvikler	Dagens Næringsliv	2	4	Snarest
71	Junior Java-utvecklare till molntjänst i Linköping	TaxiCaller Nordic AB	5	2	2017-07-11
72	Junior .NET-utvecklare till voestalpine group-IT i Karlstad	Academic Work	10	2	2017-07-14
73	Junior sytemtestare	Framtiden AB	3	2	2017-07-21
75	Webutvikler	Kvalitetskontroll AS	11	2	Snarest
67	Mjukvaruutvecklare	Prevas	5	4	2017-05-31
78	Junior webbutvecklare (WordPress, PHP & JavaScript	Angry Creative AB	4	2	2017-07-31
79	Mjukvaruutvecklare	Wemotion AB	5	2	2017-08-04
77	Junior .NET-utvecklare	Academic Work	3	4	2017-07-16
56	Skarpa utvecklare inom C# till Dfind IT	Dfind IT	5	4	2017-06-30
74	Systemutvecklare C# och .NET i Linköping eller Norrköping	Sogeti	5	4	2017-06-28
81	.Net-utvecklare till SYKES	Academic Work	3	4	2017-07-20
63	Javautvecklare	Dfind IT	5	4	2017-06-30
82	Softwareutvikler	Cuboid	12	2	Snarest
84	Junior systemutvecklare till expansiva Proclient System	Studentwork	3	2	2017-06-30
86	Utviklere	Statens Pensjonskasse	2	2	2017-08-14
87	App-utveckling	Framtiden AB	5	2	2017-08-13
93	Programmerer	Logiq	1	1	2017-08-06
94	Javautvikler	Bokbasen via Experis	2	2	2017-07-31
91	Junior Java backendutvecklare till Linköping	Avenda Solutions AB	5	2	2017-07-25
83	Webutvikler/Programmerer	High Tech Solutions AS	13	2	2017-07-17
102	Utvikler	Amesto Solutions AS	14	1	Snarest
99	Junior .NET utvecklare till stark växande bolag	Framtiden AB	3	2	2017-07-05
90	.NET-utvecklare	Mecenat via Academic Work	3	4	2017-07-27
92	Junior .NET utvecklare till StroedeRalton	Academic Work	5	4	2017-07-29
88	Relationsfokuserad backendutvecklare	Per & Per via Academic Work	5	4	2017-07-24
2	Systemutvecklare	Briljant (via Academic Work)	4	4	2016-12-10
1	Utvecklare	Proactive Gaming	4	4	2016-11-01
80	Junior Javautvecklare till Rejlers Embriq	Academic Work	3	4	2017-07-17
96	Webutvikler, front-end	Questback via Academic Work	2	4	2017-07-31
125	Interessebrev Media Markt	Media Markt	3	2	Ingen
113	Java-utvikler	EVRY Financial Services	2	2	2017-07-28
115	Nyutdannet med interesse for både kommunikasjonsteknologi og programmering?	GET via Academic Work	2	4	2017-07-18
119	Systemutvecklare C# / .NET	ÅF AB	5	1	2017-09-03
121	Utvecklare inom .NET (C# & VB)	Lämneå Bruk via Xamera	16	1	2017-09-15
123	Bli IT-konsult på 12 veckor	Academy via Academic Work	5	4	2017-08-28
126	Interessebrev Media Markt	Media Markt	4	2	Ingen
127	Interessebrev Media Markt	Media Markt	5	2	Ingen
106	Juniora utvecklare	Sigma IT Consulting	3	2	2017-08-05
114	Utvikler	Deichmanske bibliotek	2	2	2017-08-04
100	Systemutvecklare/Programmerare ("Sundahus söker någon som knäcker koden")	Academic Work	5	2	2017-08-04
130	Er du en kreativ systemutvikler som liker varierte oppgaver?	Data Nova AS	2	1	2017-09-08
109	.NET-utvecklare till Sigma IT Consulting	Sigma IT Consulting VÄST	3	2	2017-08-07
117	Nyutdannet webutvikler	Epinova via Academic Work	2	4	2017-07-28
112	Junior/nyexaminerad utvecklare (Norrköping)	Cryptica AB	4	2	2017-08-08
133	Utvikler i Norges mest interessante teknologimiljø	SpareBank 1	2	1	Snarest
134	Frontendutvecklare Angular/React	ÅF AB Göteborg	3	1	2017-09-21
136	Grym utvecklare som älskar systemintegration	Human IT Göteborg	3	2	2017-08-12
85	Systemutvecklare - frontend	Regionalt Cancercentrum	3	2	2017-08-13
118	Systemutvikler .NET	Sopra Steria	2	2	2017-08-14
132	Junior fullstack developer	Pexip via Academic Work	2	2	2017-08-14
139	Systemutvecklare	Star Republic	3	2	2017-08-14
140	.NET-utvecklare	PAf Rekrytering AB	3	1	2017-09-17
141	Frontend utvecklare	PAf Rekrytering AB	3	1	2017-09-17
142	C# utvecklare	Diadrom via PAf Rekrytering AB	3	1	2017-09-17
97	Mjukvaruutvecklare	Conmore Ingenjörsbyrå	3	4	2017-08-11
120	Programmerare	Indentive via Academic Work	5	2	2017-08-18
116	Systemutvikler	Norsvin	15	2	2017-08-20
131	Systemutviklere	UKE - Utviklings- og kompetanseetaten	2	2	2017-08-20
147	Webbutvecklare	Euronetics via Academic Work	5	1	2017-09-15
148	Junior utvecklare inom C och C++	Tieto via Academic Work	10	1	2017-09-15
151	Frontend-utvecklare till växande företag	Framtiden	3	1	2017-09-05
152	Junior eller senior systemutvecklare	KFX HR-partner Syd AB	18	1	2017-09-30
154	1-4 systemutvecklare	Linköpings universitet\n	5	1	2017-09-14
155	1-2 frontend-utvecklare	Linköpings universitet	5	1	2017-09-14
156	Junior utvecklare! (C#)	Framtiden AB	5	1	2017-09-07
157	.NET-utvecklare	Netadmin Systems via Dfind IT	5	1	2017-10-31
159	.NET-utvecklare till webbyrå med välkända kunder	Webbyrån Petras via Academic Work	19	1	2017-09-17
160	Systemutvecklare till kommande uppdrag	Dfind IT	18	1	2017-09-17
122	Junior Java-utvecklare till molntjänst i Linköping	TaxiCaller Nordic AB	5	2	2017-08-22
107	.NET/C# utvecklare	HiQ Accelerated Concept Evaluation AB	5	2	2017-08-20
162	Front-endutvecklare med intresse för helheter	Framtiden AB	5	1	2017-09-08
163	Javautvecklare	Schoolsoft via Bravura	5	1	2017-09-08
164	Junior programmerare	ALcontrol via Xamera	5	1	2017-10-18
111	Front-End utvecklare	Infor via Academic Work	5	4	2017-08-10
101	Utvikler med 1-2 års erfaring	Skog-Data AS	2	4	2017-07-28
95	Systemutvecklare C#/.NET	LIMAB AB	3	2	2017-08-28
129	Utvikler - IKT	Utlendingsnemnda	2	2	2017-08-28
165	C# utvecklare mot webb med enterprenörsanda	Framtiden AB	3	1	2017-09-13
137	Systemutvecklare	Experis IT	3	4	2017-08-30
124	.NET-utvecklare	HiQ Göteborg	3	4	2017-08-28
158	Frontend Developer	SKF	3	2	2017-08-30
103	Fullstackutvecklare .NET till Combitechs utvecklingsteam i Linköping	Combitech AB	5	2	2017-08-31
104	Fullstackutvecklare .NET till Combitechs utvecklingsteam i Norrköping	Combitech AB	4	2	2017-08-31
161	IT-konsulent	Rygge kommune	20	2	2017-08-31
146	Datavarehusutvikler	Skatteetaten	2	2	2017-08-31
98	Software Engineer	IFS	5	2	2017-08-31
105	Junior utvecklare	Decerno	3	2	2017-08-31
110	Utvecklare/programmerare molnbaserade tjänster	EXSENS AB	3	2	2017-08-31
138	.Net Utvecklare	Lifeplan via Benify AB Göteborg	3	4	2017-08-31
135	Linuxspecialist	Human IT Göteborg	3	4	2017-08-18
149	Junior utvecklare till företag i Göteborg	Crepido via Framtiden	3	2	2017-09-01
150	Inhouse .Net-utvikler	MODIS Norge	17	2	2017-09-01
153	Javautvikler innen bank og finans	EVRY Financial Service	2	2	2017-09-01
166	Junior Backendutvecklare till internationalt IT-konsultbolag	Framtiden AB	18	1	2017-09-08
169	Programmerare	ALcontrol Laboratories via Industrikompetens i Östergötland	5	1	2017-09-22
170	.Net utvecklare	Contribe Göteborg	3	1	2018-01-17
171	Junior C-utvecklare som vill jobba med nyutveckling	Axis via Academic Work	21	1	2017-09-19
172	.Net utvecklare	Contribe Malmö	18	1	2017-09-17
173	JavaDeveloper	Contribe Malmö	18	1	2018-01-17
143	Javautvikler	IT People4you	2	2	2017-08-22
144	Frontendutvikler	Drofus AS	2	2	2017-08-22
68	Mjukvaruutvecklare	Ericsson via Academic Work	5	4	Snarest
178	Junior applikationsutvecklare med ett öga för problemlösning	Apetan via Xamera AB	5	1	2017-09-15
179	Programvaruutvecklare	i3tex	3	1	2017-09-22
181	Junior Business Intelligence Administrator till framgångsrikt bolag	Dfind IT	18	1	2017-09-17
183	Mjukvaruutvecklare med intresse för produktionssystem	Axis Communications	21	1	2017-09-10
174	.NET utvecklare	Stratsys	3	1	2017-09-13
182	Junior programmerare till framtida uppdrag	Studentconsulting	3	1	2017-09-14
185	Junior webbutvecklare inom C#	Directkonsult via Academic Work	3	1	2017-09-23
168	Systemutvikler	NettPost AS	2	2	2017-08-24
176	Systemutvecklare till växande IT-konsultföretag	Framtiden AB	4	2	2017-08-25
177	Systemutvecklare till framträdande IT-koncern	Framtiden AB	5	2	2017-08-25
186	Konsulent	SuperOffice Norge AS	2	1	2017-10-02
187	Kodeknekker	SnapTV AS	2	3	Snarest
188	Nyfiken och driven .Net utvecklare mot web	Framtiden AB	3	1	2017-09-22
145	.NET Systemutvikler	Easybank ASA	2	4	2017-08-18
190	Backend/Full-stack Developer	Cloud Insurance AS	2	1	2017-09-03
191	Junior systemutvecklare	ESAB via Experis	3	1	2017-09-24
193	Nyexad utvecklare med fokus på backend	Axis Communications via Academic Work	21	1	2017-09-25
167	Webutvikler	OXX AS	2	2	2017-08-27
194	.Net utvikler med ønske om nye utfordringer	Visma Consulting AS	2	1	2017-09-04
195	Systemutvikler .Net	dRofus AS	2	1	Snarest
196	Systemutvecklare	Lindorff via Dfind IT	3	1	2017-10-25
197	Junior fullstackutvecklare till expansiv digitalbyrå	Framtiden	3	1	2017-09-22
198	Junior utvecklare	WSP via Academic Work	19	1	2017-09-26
180	Javautvikler	UBConnect	2	2	2017-08-29
184	Junior frontend-utvecklare	Provide IT Sweden AB	3	2	2017-08-29
128	IT-tekniker onsite till kommande uppdrag	Infocare	4	4	2017-08-30
108	Javautvecklare med schyssta variabler	HiQ Accelerated Concept Evaluation AB	5	4	2017-08-20
192	Är du duktig på PHP och söker ett härligt team att ingå i?	Human IT	18	2	2017-08-31
175	Fullstack utvikler	Glasspaper People AS	2	2	2017-09-01
189	Front-end utvikler	Distribution Innovations AS	2	2	2017-09-01
199	Systemutvikler	Azets People AS Oslo	2	1	2017-09-05
200	Har du lyst til å lage brukervennlige og moderne webapps?	Posten Norge AS	2	1	2017-09-06
201	Programmerare i molnet	Axis Communications	21	1	2017-09-22
202	Problemlösande PHP-utvecklare	JGL via Xamera	5	1	2017-10-30
203	Utvecklare inom C/C++, .NET, C#, Java, etc	Q Bemanning & Rekrytering	5	1	2017-09-28
204	Java-utvecklare	HiQ Göteborg AB	3	1	2017-09-17
89	Fullstackutvecklare (.NET)	Ezy via Dfind IT	3	4	2017-08-30
205	Norwegian speaking Technical Support Professional to our Nordic team	Apsis International AB	18	2	2017-09-29
\.


--
-- Name: soknadid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('soknadid_seq', 205, true);


--
-- Data for Name: status; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY status (statusid, status) FROM stdin;
1	Registrert
2	Sendt
4	Avvist
3	Interessert, mulig intervju
6	Godtatt, klar for jobb
5	Søknad skrevet, men ikke sendt
\.


--
-- Name: statusid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('statusid_seq', 4, true);


--
-- Data for Name: sted; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY sted (stedid, stedsnavn, landid) FROM stdin;
1	Sarpsborg	1
2	Oslo	1
3	Göteborg	2
4	Norrköping	2
5	Linköping	2
6	Stockholm	2
7	Halden	1
8	Moss	1
9	Fredrikstad	1
10	Karlstad	2
11	Rong	1
12	Drammen	1
13	Vormedal	1
14	Bergen	1
15	Hamar	1
16	Finspång	2
17	Ski	1
18	Malmö	2
19	Helsingborg	2
20	Rygge	1
21	Lund	2
\.


--
-- Name: stedid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('stedid_seq', 21, true);


--
-- Name: user_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('user_id_seq', 1, false);


--
-- Name: land_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY land
    ADD CONSTRAINT land_pkey PRIMARY KEY (landid);


--
-- Name: soknad_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_pkey PRIMARY KEY (soknadid);


--
-- Name: status_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY status
    ADD CONSTRAINT status_pkey PRIMARY KEY (statusid);


--
-- Name: sted_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT sted_pkey PRIMARY KEY (stedid);


--
-- Name: unik_status; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY status
    ADD CONSTRAINT unik_status UNIQUE (status);


--
-- Name: unikt_land; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY land
    ADD CONSTRAINT unikt_land UNIQUE (land);


--
-- Name: unikt_sted; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT unikt_sted UNIQUE (stedsnavn);


--
-- Name: trg_nysoknad; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nysoknad AFTER INSERT ON soknad FOR EACH ROW EXECUTE PROCEDURE nysoknadid();


--
-- Name: trg_nyttland; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nyttland AFTER INSERT ON land FOR EACH ROW EXECUTE PROCEDURE nylandid();


--
-- Name: trg_nyttsted; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nyttsted AFTER INSERT ON sted FOR EACH ROW EXECUTE PROCEDURE nystedid();


--
-- Name: trg_oppdatersoknad; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_oppdatersoknad AFTER UPDATE ON soknad FOR EACH ROW EXECUTE PROCEDURE updatesoknad();


--
-- Name: soknad_statusid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_statusid_fkey FOREIGN KEY (statusid) REFERENCES status(statusid);


--
-- Name: soknad_stedid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_stedid_fkey FOREIGN KEY (stedid) REFERENCES sted(stedid);


--
-- Name: sted_landid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT sted_landid_fkey FOREIGN KEY (landid) REFERENCES land(landid);


--
-- Name: public; Type: ACL; Schema: -; Owner: pgsql
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM pgsql;
GRANT ALL ON SCHEMA public TO pgsql;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--


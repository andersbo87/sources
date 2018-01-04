--
-- PostgreSQL database dump
--

-- Dumped from database version 10.1
-- Dumped by pg_dump version 10.1

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
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
-- Name: empty(text); Type: FUNCTION; Schema: public; Owner: andersbo
--

CREATE FUNCTION empty(text) RETURNS boolean
    LANGUAGE sql IMMUTABLE
    AS $_$ SELECT $1 ~ '^[[:space:]]*$'; $_$;


ALTER FUNCTION public.empty(text) OWNER TO andersbo;

--
-- Name: FUNCTION empty(text); Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON FUNCTION empty(text) IS 'Sjekke innholdet i en streng. Returnerer sann om strengen er tom eller bare inneholder mellomrom, og falsk ellers.';


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
if NEW.motivasjon != OLD.motivasjon
then
raise notice 'Søknaden med ID % har fått endret motivasjon fra % til %.', OLD.soknadid, OLD.motivasjon, NEW.motivasjon;
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
    soknadsfrist text NOT NULL,
    motivasjon text,
    CONSTRAINT chk CHECK ((NOT empty(tittel))),
    CONSTRAINT chkbedriftnotempty CHECK ((NOT empty(bedrift))),
    CONSTRAINT chksoknadsfristnotempty CHECK ((NOT empty(soknadsfrist)))
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
    status.status,
    soknad.motivasjon
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
-- Data for Name: soknad; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY soknad (soknadid, tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon) FROM stdin;
4	IT-tekniker	Alina Systems i Östersund AB	4	2	2016-12-15	
5	Systemutvecklare .NET	Combitech	4	4	2016-11-19	
6	Databasutvecklare	Migrationsverket	4	2	2016-10-30	
7	Systemutvecklare Java	Migrationsverket	4	4	2016-11-21	
8	Systemutvecklare	Montico	4	2	2016-11-30	
9	Applikationsutvecklare inriktning Integrationer	Sjöfartsverket	4	2	2016-11-27	
10	Systemförvaltare Kontorsstöd	SMHI	4	2	2016-11-24	
11	Butikssäljare 75 %	Stadium Norrköping	4	4	2016-11-13	
13	Utvikler	NAF	2	4	2016-11-14	
14	.NET C# Systemutvecklare	Teknomedia	4	4	2016-12-31	
15	Product Coordinator	Stadium Norrköping	4	4	2016-12-13	
22	Webbutvecklare	TaxiCaller Nordic AB	5	2	2017-01-10	
20	Systemarkitekt	JobBusters AB	4	4	2017-01-30	
19	Helpdeskmedarbetare med servicekänsla	Perido	4	2	2016-12-29	
18	Servicetekniker	SFT Bredbandsgruppen AB	4	2	2016-12-23	
21	.NET-utvecklare	Revide (via Academic Work)	4	4	2017-01-09	
23	.NET-utvecklare	Consid	4	2	2017-01-14	
25	Driven supportspecialist med brinnande kundfokus	Industrikompetens i Östergötland AB	4	2	2017-01-31	
24	JAVA-utvecklare Norrköping	Cybercom Group AB	4	4	2017-01-15	
26	Full Stack Developer	Prevas	4	2	2017-01-31	
27	Junior .NET utvikler	Rett Bemanning Oslo Vest	2	4	2017-01-15	
28	Junior Applikationsutvecklare	Apetan	5	2	2017-01-20	
29	Java-utvecklare Norrköping	Consid	4	2	2017-02-10	
30	Vetenskapsprogrammerare med goda systemutvecklingskunskaper	SMHI	4	4	2017-01-29	
31	Webbutvecklare	Compriser AB	4	2	2017-01-31	
32	.NET-utviklere	Lånekassen	2	2	2017-01-23	
33	Systemutvecklare	i3tex	4	2	2017-02-12	
34	Webbutvecklare	i3tex	4	4	2017-02-12	
36	Norsktalande supporttekniker i Linköping	Dfind IT	5	4	2017-01.31	
37	Junior frontend-utvecklare	Nethouse via Academic Work	5	4	2017-03-07	
38	Webbutvecklare/Applikationsutvecklare	Ventiro AB	4	4	2017-02-28	
39	Systemutvecklare till inhouseverksamhet	Framtiden AB	4	4	2017-03-22	
40	Junior mjukvaruutvecklare	Etteplan Industry AB	5	2	2017-03-12	
41	Mjukvaruutvecklare med genuint teknikintresse	SysPartner via Xamera	5	2	2017-04-22	
42	Utvecklare	Millenway Development AB	4	2	2017-02-28	
43	Systemutvecklare	XLENT	4	4	2017-03-09	
44	Systemutvecklare till Holmen	Academic Work	4	2	2017-04-20	
45	Utvikler	eSmart Systems	7	4	Snarest	
46	Softwareutvikler	Hiddn Security AS	2	2	2017-04-06	
47	Nyexaminerade mjukvaruutvecklare	Alten Sverige AB	5	4	2017-04-27	
48	Softwareutvikler	Prediktor AS	9	4	2017-05-14	
49	.NET/C# utvecklare i Norrköping	HiQ Accelerated Concept Evaluation AB	4	4	2017-04-23	
50	Systemutvecklare/Programmerare	InspireIT	4	2	2017-05-10	
51	Systemutvikler	NettPost AS (Bærum)	2	2	2017-04-30	
52	Skarpa utvecklare inom C# till Dfind IT	Dfind IT	5	4	2017-06-30	
53	Junior C#/.NET-utvecklare	Arenius Schröder & Besterman Talents AB	5	4	2017-04-28	
54	System Developer	E2U Systems	9	2	Snarest	
55	Systemutvecklare	Combitech AB	5	2	2017-05-28	
56	Briljant systemutvecklare	Briljant (via Academic Work)	4	4	2017-06-02	
57	Systemutvikler	Oslo Universitetssykehus	2	2	2017-05-21	
58	Systemutvikler	Kredinor via Academic Work	2	4	2017-05-18	
59	Javautvecklare	Dfind IT	5	4	2017-06-30	
60	Junior Full Stack Developer	Framtiden AB	5	4	2017-05-27	
61	Juniora systemutvecklare	Netgain via Framtiden	4	2	2017-05-13	
62	Webbutvecklare	Svenskalag.se	4	4	2017-06-01	
63	Mjukvaruutvecklare	Prevas	5	4	2017-05-31	
64	Mjukvaruutvecklare	Ericsson via Academic Work	5	4	Snarest	
65	Webutvikler	Dagens Næringsliv	2	4	Snarest	
67	Junior Java-utvecklare till molntjänst i Linköping	TaxiCaller Nordic AB	5	2	2017-07-11	
68	Junior .NET-utvecklare till voestalpine group-IT i Karlstad	Academic Work	10	2	2017-07-14	
69	Junior sytemtestare	Framtiden AB	3	2	2017-07-21	
70	Systemutvecklare C# och .NET i Linköping eller Norrköping	Sogeti	5	4	2017-06-28	
71	Webutvikler	Kvalitetskontroll AS	11	2	Snarest	
72	Junior programmerare till framtida uppdrag	StudentConsulting	3	4	2017-06-30	
73	Junior .NET-utvecklare	Academic Work	3	4	2017-07-16	
74	Junior webbutvecklare (WordPress, PHP & JavaScript	Angry Creative AB	4	4	2017-07-31	
75	Mjukvaruutvecklare	Wemotion AB	5	2	2017-08-04	
76	Junior Javautvecklare till Rejlers Embriq	Academic Work	3	4	2017-07-17	
77	.Net-utvecklare till SYKES	Academic Work	3	4	2017-07-20	
78	Softwareutvikler	Cuboid	12	2	Snarest	
79	Webutvikler/Programmerer	High Tech Solutions AS	13	2	2017-07-17	
80	Junior systemutvecklare till expansiva Proclient System	Studentwork	3	2	2017-06-30	
81	Systemutvecklare - frontend	Regionalt Cancercentrum	3	2	2017-08-13	
82	Utviklere	Statens Pensjonskasse	2	2	2017-08-14	
83	App-utveckling	Framtiden AB	5	2	2017-08-13	
244	Traineeprogram	StudentCounsulting	2	2	Snarest	
254	Javautvikler med front-end fokus	Tripletex via DFind IT	2	2	Snarest	
256	Utviklere	TeleComputing Norway AS	28	2	2017-11-20	
17	Testutveckling inom Mjukvara	i3tex AB	4	4	2016-12-20	
85	Fullstackutvecklare (.NET)	Ezy via Dfind IT	3	4	2017-08-30	
86	.NET-utvecklare	Mecenat via Academic Work	3	4	2017-07-27	
87	Junior Java backendutvecklare till Linköping	Avenda Solutions AB	5	2	2017-07-25	
88	Junior .NET utvecklare till StroedeRalton	Academic Work	5	4	2017-07-29	
89	Javautvikler	Bokbasen via Experis	2	2	2017-07-31	
90	Systemutvecklare C#/.NET	LIMAB AB	3	2	2017-08-28	
91	Webutvikler, front-end	Questback via Academic Work	2	4	2017-07-31	
92	Mjukvaruutvecklare	Conmore Ingenjörsbyrå	3	4	2017-08-11	
93	Software Engineer	IFS	5	4	2017-08-31	
94	Junior .NET utvecklare till stark växande bolag	Framtiden AB	3	2	2017-07-05	
96	Utvikler med 1-2 års erfaring	Skog-Data AS	2	4	2017-07-28	
97	Utvikler	Amesto Solutions AS	14	1	Snarest	
98	Fullstackutvecklare .NET till Combitechs utvecklingsteam i Linköping	Combitech AB	5	4	2017-08-31	
99	Fullstackutvecklare .NET till Combitechs utvecklingsteam i Norrköping	Combitech AB	4	2	2017-08-31	
100	Junior utvecklare	Decerno	3	2	2017-08-31	
101	Juniora utvecklare	Sigma IT Consulting	3	2	2017-08-05	
102	.NET/C# utvecklare	HiQ Accelerated Concept Evaluation AB	5	2	2017-08-20	
103	Javautvecklare med schyssta variabler	HiQ Accelerated Concept Evaluation AB	5	4	2017-08-20	
104	.NET-utvecklare till Sigma IT Consulting	Sigma IT Consulting VÄST	3	2	2017-08-07	
105	Utvecklare/programmerare molnbaserade tjänster	EXSENS AB	3	2	2017-08-31	
106	Front-End utvecklare	Infor via Academic Work	5	4	2017-08-10	
107	Junior/nyexaminerad utvecklare (Norrköping)	Cryptica AB	4	2	2017-08-08	
108	Java-utvikler	EVRY Financial Services	2	2	2017-07-28	
109	Utvikler	Deichmanske bibliotek	2	2	2017-08-04	
110	Nyutdannet med interesse for både kommunikasjonsteknologi og programmering?	GET via Academic Work	2	4	2017-07-18	
111	Systemutvikler	Norsvin	15	2	2017-08-20	
112	Nyutdannet webutvikler	Epinova via Academic Work	2	4	2017-07-28	
113	Systemutvikler .NET	Sopra Steria	2	2	2017-08-14	
114	Systemutvecklare C# / .NET	ÅF AB	5	4	2017-09-03	
115	Programmerare	Indentive via Academic Work	5	2	2017-08-18	
116	Bli IT-konsult på 12 veckor	Academy via Academic Work	5	4	2017-08-28	
117	.NET-utvecklare	HiQ Göteborg	3	4	2017-08-28	
118	Interessebrev Media Markt	Media Markt	3	2	Ingen	
119	Interessebrev Media Markt	Media Markt	4	2	Ingen	
120	Interessebrev Media Markt	Media Markt	5	2	Ingen	
121	IT-tekniker onsite till kommande uppdrag	Infocare	4	4	2017-08-30	
122	Utvikler - IKT	Utlendingsnemnda	2	4	2017-08-28	
123	Er du en kreativ systemutvikler som liker varierte oppgaver?	Data Nova AS	2	2	2017-09-08	
124	Systemutviklere	UKE - Utviklings- og kompetanseetaten	2	2	2017-08-20	
125	Junior fullstack developer	Pexip via Academic Work	2	4	2017-08-14	
126	Utvikler i Norges mest interessante teknologimiljø	SpareBank 1	2	4	Snarest	
127	Frontendutvecklare Angular/React	ÅF AB Göteborg	3	4	2017-09-21	
128	Linuxspecialist	Human IT Göteborg	3	4	2017-08-18	
129	Grym utvecklare som älskar systemintegration	Human IT Göteborg	3	2	2017-08-12	
130	Systemutvecklare	Experis IT	3	4	2017-08-30	
131	.Net Utvecklare	Lifeplan via Benify AB Göteborg	3	4	2017-08-31	
132	Systemutvecklare	Star Republic	3	2	2017-08-14	
133	.NET-utvecklare	PAf Rekrytering AB	3	4	2017-09-17	
134	Frontend utvecklare	PAf Rekrytering AB	3	2	2017-09-17	
135	C# utvecklare	Diadrom via PAf Rekrytering AB	3	2	2017-09-17	
136	Javautvikler	IT People4you	2	2	2017-08-22	
137	Frontendutvikler	Drofus AS	2	2	2017-08-22	
138	.NET Systemutvikler	Easybank ASA	2	4	2017-08-18	
139	Datavarehusutvikler	Skatteetaten	2	4	2017-08-31	
140	Webbutvecklare	Euronetics via Academic Work	5	4	2017-09-15	
142	Junior utvecklare till företag i Göteborg	Crepido via Framtiden	3	4	2017-09-01	
143	Inhouse .Net-utvikler	MODIS Norge	17	2	2017-09-01	
144	Frontend-utvecklare till växande företag	Framtiden	3	4	2017-09-05	
145	Junior eller senior systemutvecklare	KFX HR-partner Syd AB	18	2	2017-09-30	
146	Javautvikler innen bank og finans	EVRY Financial Service	2	2	2017-09-01	
147	1-4 systemutvecklare	Linköpings universitet\n	5	4	2017-09-14	
148	1-2 frontend-utvecklare	Linköpings universitet	5	2	2017-09-14	
149	Junior utvecklare! (C#)	Framtiden AB	5	2	2017-09-07	
150	Frontend Developer	SKF	3	2	2017-08-30	
151	.NET-utvecklare till webbyrå med välkända kunder	Webbyrån Petras via Academic Work	19	4	2017-09-17	
152	Systemutvecklare till kommande uppdrag	Dfind IT	18	4	2017-09-17	
153	IT-konsulent	Rygge kommune	20	2	2017-08-31	
155	Javautvecklare	Schoolsoft via Bravura	5	4	2017-09-08	
154	Front-endutvecklare med intresse för helheter	Framtiden AB	5	2	2017-09-08	
156	Junior programmerare	ALcontrol via Xamera	5	4	2017-10-18	
157	C# utvecklare mot webb med enterprenörsanda	Framtiden AB	3	4	2017-09-13	
158	Junior Backendutvecklare till internationalt IT-konsultbolag	Framtiden AB	18	2	2017-09-08	
159	Webutvikler	OXX AS	2	4	2017-08-27	
160	Systemutvikler	NettPost AS	2	2	2017-08-24	
161	Programmerare	ALcontrol Laboratories via Industrikompetens i Östergötland	5	4	2017-09-22	
163	.Net utvecklare	Contribe Malmö	18	4	2017-09-17	
164	JavaDeveloper	Contribe Malmö	18	1	2018-01-17	
165	.NET utvecklare	Stratsys	3	4	2017-09-13	
166	Fullstack utvikler	Glasspaper People AS	2	2	2017-09-01	
167	Systemutvecklare till växande IT-konsultföretag	Framtiden AB	4	4	2017-08-25	
168	Systemutvecklare till framträdande IT-koncern	Framtiden AB	5	4	2017-08-25	
169	Programvaruutvecklare	i3tex	3	4	2017-09-22	
170	Javautvikler	UBConnect	2	2	2017-08-29	
171	Junior Business Intelligence Administrator till framgångsrikt bolag	Dfind IT	18	4	2017-09-17	
172	Junior programmerare till framtida uppdrag	Studentconsulting	3	2	2017-09-14	
173	Mjukvaruutvecklare med intresse för produktionssystem	Axis Communications	21	4	2017-09-10	
175	Junior webbutvecklare inom C#	Direktkonsult via Academic Work	3	4	2017-09-23	
174	Junior frontend-utvecklare	Provide IT Sweden AB	3	2	2017-08-29	
176	Konsulent	SuperOffice Norge AS	2	2	2017-10-02	
177	Kodeknekker	SnapTV AS	2	4	Snarest	
178	Nyfiken och driven .Net utvecklare mot web	Framtiden AB	3	4	2017-09-22	
179	Front-end utvikler	Distribution Innovations AS	2	4	2017-09-01	
180	Backend/Full-stack Developer	Cloud Insurance AS	2	2	2017-09-03	
181	Junior systemutvecklare	ESAB via Experis	3	4	2017-09-24	
183	Nyexad utvecklare med fokus på backend	Axis Communications via Academic Work	21	4	2017-09-25	
184	.Net utvikler med ønske om nye utfordringer	Visma Consulting AS	2	2	2017-09-04	
185	Junior fullstackutvecklare till expansiv digitalbyrå	Framtiden	3	4	2017-09-22	
186	Junior utvecklare	WSP via Academic Work	19	4	2017-09-26	
187	Systemutvikler	Azets People AS Oslo	2	4	2017-09-05	
188	Har du lyst til å lage brukervennlige og moderne webapps?	Posten Norge AS	2	2	2017-09-06	
189	Programmerare i molnet	Axis Communications	21	4	2017-09-22	
190	Utvecklare inom C/C++, .NET, C#, Java, etc	Q Bemanning & Rekrytering	5	2	2017-09-28	
191	Java-utvecklare	HiQ Göteborg AB	3	2	2017-09-17	
192	Norwegian speaking Technical Support Professional to our Nordic team	Apsis International AB	18	2	2017-09-29	
193	Junior utvecklare	IDP	3	2	2017-10-15	
194	Junior systemutvecklare till ett trygt företag i Malmö	Framtiden AB	18	2	2017-09-22	
195	PHP-programmerare	Webbhuset via Academic Work	3	4	2017-10-02	
197	Junior utvikler	Bouvet via Academic Work	2	4	Snarest	
196	Är du en systemutvecklare som vill utvecklas	PAf Rekrytering AB	3	2	2017-11-03	
198	JAVA	Technogarden Norge	2	2	Snarest	
199	Frontend/Backend systemutvikler	Etterretningstjenesten	2	2	2017-09-22	
200	Javautvecklare sökes till innovativt företag i Göteborg	Framtiden AB	3	4	2017-09-29	
201	Junior Fullstack-utvecklare	Creditsafe via Sigma IT Consulting	3	2	2017-10-31	
202	Systemutvikler .NET	IT People4you	2	2	Snarest	
203	C#-utvecklare	BILIA via Academic Work	3	4	2017-10-08	
204	Junior .NET utvecklare	Framtiden AB	3	2	2017-10-06	
205	Junior utvecklare i JavaScript med intresse för IT och Teknik	Academic Work	21	4	2017-10-08	
206	Front-Endutvikler	Arena Data via Academic Work	2	4	2017-09-18	
207	Junior webbutvecklare	Provide IT Sweden AB	3	2	2017-09-18	
209	Systemutvikler/interaksjonsdesigner	Etterretningstjenesten	2	2	2017-10-01	
210	Utvikler - Etterretning og internasjonalt samarbeid	Politiet	2	2	2017-10-09	
211	Lidenskapelige nyutdannede utviklere	SpareBank 1	2	4	2017-09-30	
212	Systemadministratör inom Linux/Unix	ELITS	5	4	2018-03-02	
213	Plattform Utvikler	Viju/Technogarden	2	4	Snarest	
214	Utvikler, konsulent til webapplikasjonsteam	TalentCo AS	2	2	2017-09-28	
215	Dyktig backendutvikler til spennende rolle i agile team	Glasspaper People	2	2	2017-09-26	
216	Junior Webbutvecklare	WooCommerce via Framtiden AB	3	4	2017-10-17	
217	Systemutvikler	Schenker AS	2	2	2017-10-08	
218	Systemutvikler .NET	OXX via Academic Work	2	4	2017-09-29	
219	Vassa Java och .NET utvecklare	Skill	3	2	2017-10-06	
220	.NET-utvecklare	Yalta via Academic Work	3	4	2017-10-23	
221	Frontend Utvikler	Personal Finance AS	2	2	2017-10-10	
222	PHP-utvecklare	Shopcorn	3	2	2017-10-04	
224	Inhouse .Net-utvikler	Columbus Norway AS	2	4	2017-10-20	
225	Systemutvecklare, 100%, tillsvidareanställning	Karlstads universitet	10	2	2017-10-26	
226	Inhouse utvikler	Svea Finans via Veksthuset	2	4	Snarest	
227	Javautvikler i Vestfold	People4you	2	2	Snarest	
228	Frontendutvikler PHP	Vendo AS	22	2	2017-11-01	
229	Junior utvecklare till internationellt företag	Framtiden AB	3	2	2017-10-31	
230	Nyfiken systemutvecklare	Dfind IT	3	2	2017-11-06	
231	Utvikler i et nyskapende kommunikasjonsnettverk	Dentsu via Academic Work	2	2	2017-10-11	
233	Programmerer, Frontend	Unicornis	2	2	2017-10-20	
234	Junior .Net utvecklare	Dynamic Smartsourcing via Framtiden	3	2	2017-11-06	
235	Nyutdannet systemutvikler	Ciber	2	2	2017-10-17	
236	Utvikler innen .Net/C#	Acando	2	4	2017-10-18	
238	Programvareutvikler - embedded	Steinsvik AS	23	2	2017-10-22	
240	Javautvikler	ITX Norge	24	2	Snarest	
242	Inhouse utvikler med kommersielt gen	Konsentra AS	2	2	2017-10-31	
243	Programvareutvikler .net	CGI Norge	1	3	2017-10-18	
223	Traineeprogram	GeoData	2	4	2017-10-15	
237	Junior Java-utvikler	Skatteetaten	2	4	2017-10-30	
241	.NET utvikler	CGI Norge	2	2	2017-11-12	
245	Utvikler/Vil du jobbe som utvikler i et selskap der du kan påvirke teknologivalg?	Dentsu Aegis Network Norge via Academic Work	2	2	2017-10-27	
246	Webutvikler/Fullstackutvikler	Vitec Software Group	2	4	Snarest	
247	Applikasjonsutvikler/Java erfaring og kompetanse innen relasjonsdatabaser?	Bisnode Norge AS	2	2	Snarest	
248	Junior .NET utvikler som brenner for programmering	IT People4you	2	2	2017-11-23	
249	Java-utviklere i Oslo, bli med i flokken vår	Kantega AS	2	4	Snarest	
250	Systemutvikler	Lovdata	2	1	2017-12-01	
251	Systemutvikler .NET	ACT Logimark	27	2	Snarest	
252	C++/QT developer	Top Temp IT AS	2	2	Snarest	
253	Utviklere	UiO (Universitetet i Oslo)	2	2	Snarest	
255	Nyutdannet utvikler og klar for en real utfordring?	Cenium via IT People4you	2	2	2017-11-26	
257	Spennende stilling som webutvikler	Multicase Norge AS	24	2	Løpende	
258	Utvikler/arkitekt som liker variasjon og trygge rammer	Redningsselskapet	2	2	2017-11-25	
260	Vil du utvikle morgendagens teknologiplattform?	Vil du utvikle morgendagens teknologiplattform?	2	2	2017-12-01	
261	Inhouse .NET utvikler	Inhouse .NET utvikler	2	2	Snarest	
262	Erfaring med .NET og C#? Lyst å jobbe med revolusjonering av helse-Norge?	Erfaring med .NET og C#? Lyst å jobbe med revolusjonering av helse-Norge?	2	2	Snarest	
263	Nyutdannet, dyktig og klar for å bidra i prosjeketer?	Bouvet Norge AS	2	2	Snarest	
264	Vil du jobbe med .NET utvikling og artificial intelligence	Vil du jobbe med .NET utvikling og artificial intelligence	2	2	2017-11-20	
265	Traineeprogram for nyutdannede innen IT	StudentConsulting	2	4	Snarest	
266	Junior .net utvikler med ambisjon om å jobbe med forretningskritiske løsninger?	ABC Data via Academic Work	2	4	2017-11-21	
267	Nyutdannet med passion for C#?	JuhlerGroup via Access Professionals	2	2	2018-01-02	
268	Vi søker både erfarne og nyutdannede systemutviklere med bachelorgrad innen IT	Sopra Steria	2	2	2017-12-13	
269	Systemutvikler	Bouvet	2	4	Snarest	
270	Full-stack programmerer	Add Novatech	30	2	2017-11-19	
271	Systemutvikler .NET	PostNord AS	2	2	Snarest	
272	C# Programmerer	SPIDER Solutions via Academic Work	2	4	2017-11-20	
273	Utviklere (Front-end/back-end/full-stack)	Dekode Interaktiv AS	2	2	Snarest	
274	Utvikler - Datavarehusteamet ("Jobbe med kul metodikk og ny teknologi?")	PRA Group	2	2	Snarest	
275	To systemutviklere til nye og spennende nasjonale IT-løsninger	Direktoratet for forvaltning og IKT (DIFI)	31	2	2017-11-19	
276	Software Utvikler	CompuGroup Medical Norway AS	2	4	2017-12-17	
279	Faglig nysgjerrig .NET utvikler	Ciber Norge AS	2	2	Snarest	
277	Javautvikler	EVRY	2	2	2017-12-20	
280	Er du en dyktig .NET utvikler og ønsker å jobbe med fullstack?	Tempus via Academic Work	2	4	2017-12-04	
281	Utvikler til spennende analyse selskap!	Nordic Bond Pricing via Academic Work	2	4	2017-12-04	
282	Nyutdannet utvikler	Netcompany	2	4	2017-11-30	
283	Konsulent utvikler .NET	Microsoft University	2	4	Snarest	
284	Applikasjonsutvikler og systemutvikler	IT People4you	25	4	2017-12-11	
285	Systemutviklere	Oslo kommune	2	4	2017-11-23	
286	PHP/Webutvikler	Jobzone Tønsberg	22	4	Snarest	
287	Systemutvikler - Bring Express - Har du lyst til å lage brukervennlige og moderne webapps?	Posten Norge AS	2	2	2017-12-22	
288	Fullstackutvikler/Fullstack software developer	Modis	2	5	2018-01-01	
289	Systemutvikler - privatmarkedet	Posten Norge AS	2	4	2017-12-22	
290	Trainee	iStone via Academic Work	2	4	2017-13-12	
291	Systemutvikler C# .NET	EVRY	32	2	2018-01-09	
292	PHP Web utvikler	Brandgate AS	2	2	2017-12-15	
294	Applikasjonsutvikling - Søker junior .NET-utvikler til spennende selskap i vekst!	IT People4you	2	2	2017-12-20	
293	SQL-utvikler	Bisnode AS	2	4	Snarest	
295	.NET-utvikler/Konsulent (Ønsker du å jobbe på spennende prosjekter? Vi søker junior .NET-utvikler til fast stilling)	Bouvet	2	4	Snarest	
296	Nyutdannet systemutvikler (Er du nyutdannet og klar for en kickstart på karrieren)	Capgemini Norge AS	2	4	Snarest	
297	Vil du utvikle morgendagens teknologiplattform?	INTILITY AS	2	4	2017-12-01	
298	.NET-utvikler	EVRY	2	2	2018-01-07	
299	Lyst til å jobbe med grafisk brukergrensesnitt?	Nevion via Academic Work	2	2	2017-12-31	
300	Er du en dyktig Java-utvikler	Weldindustry via DFind	2	2	Snarest	
301	En mulighet en systemutvikler med .NET-erfaring ikke vil gå glipp av	Cenium Scandinavia via IT People4you	2	2	2017-12-15	
303	Systemutvikler .NET (Skybasert programvarehus i sterk vekst søker .NET-systemutvikler	Xlent via Glasspaper People	2	2	Snarest	
302	Fullstack utvikler	Finn	2	4	2018-01-15	
304	Senior eller junior Javautvikler?	Express Rekruttering AS	2	2	Snarest	
305	Drømmer du om å jobbe som utvikler i et spennende teknologiselskap?	Phonect via Academic Work	2	2	2017-01-26	
306	Shiplog søker webutviklere i Oslo eller Kristiansund	Shiplog AS	33	2	2017-01-21	
307	Er du Convert Groups nye PHP-utvikler?	Convert Groups via Academic Work	2	4	2018-01-25	
308	Systemutviklere PHP/"Vi trenger flere dyktige, kreative og løsningsorienterte utviklere!"	Spinner Labs	22	2	2017-12-27	
309	Applikasjonsutvikler/konsulent/"Systemutviklere innen Java søkes til IPCO AS"	IPCO AS	7	2	2017-12-27	
312	Junior C#/DB utvikler	Infront ASA	2	1	2017-12-28	
12	Utvecklare/programmerare med inriktning mot 3D på webben	SWECO AB	4	4	2016-10-30	
16	Fälttekniker, Norrköping	Barona Human Resource Services AB	4	2	2016-12-31	 
35	Systemutvecklare .NET till inhouseverksamhet i Norrköping	Combitech	4	2	2017-05-31	
66	Backendutvecklare sökes till Linköping	Framtiden AB	5	4	2017-06-30	
84	Relationsfokuserad backendutvecklare	Per & Per via Academic Work	5	4	2017-07-24	
95	Systemutvecklare/Programmerare ("Sundahus söker någon som knäcker koden")	Academic Work	5	4	2017-08-04	
141	Junior utvecklare inom C och C++	Tieto via Academic Work	10	4	2017-10-24	
162	Junior C-utvecklare som vill jobba med nyutveckling	Axis via Academic Work	21	4	2017-09-19	
182	Är du duktig på PHP och söker ett härligt team att ingå i?	Human IT	18	4	2017-08-31	
208	Junior C/C# utvecklare för arbete inom Industriell IT	Framtiden AB	3	4	2017-10-03	
232	Junior systemutvecklare av spännande IT-lösningar för samhällsbyggnad	Framtiden AB	3	2	2017-10-25	
239	Interesse for programmering i Java og/eller Python?	Conmodo	2	4	2017-10-18	
259	Vil du være med å utvikle neste generasjons maritime navigasjonsløsninger?	Telko AS	29	1	2017-12-01	
278	Webutvikler - Kan du vise til grunnleggende kompetanse på Microsoftstacken? PayEx søker junior .NET-utvikler	PayEx via Academic Work	2	4	2017-12-04	
310	Server Developer	Infront ASA	2	2	2017-12-27	
311	Full-stack utvikler til spennende og fremtidsrettet stilling	Inspera AS	2	2	2018-01-29	
313	Front-end utvkler/"Skybasert programvarehus i sterk vekst søker front-end utvikler"	Xledger	2	2	2017-12-29	
314	Webutvikler/"Junior programmerer til Sensio"	Sensio via Academic Work	2	2	2018-01-15	
315	.NET utvikler/"Lyst til å jobbe med .NET teknologi og maskinlæring in-house?"	Montel	2	2	2017-12-28	
316	Dyktig utvikler? Eller ambisjoner om å bli det?	Experis	14	2	2018-01-24	
3	Webbdesigner/Frontendutvecklare/Webbutvecklare	Trollweb Solutions AB	4	4	2016-09-08	
317	Nyutdannet eller junior utvikler som vil jobbe med bare bra folk?	Bouvet via Academic Work	2	1	Snarest	Det som motiverer meg når det gjelder selve bedriften er at de tilbyr en variert hverdag, gode betingelser, jobb med anerkjente kunder og egen mulighet til å påvirke egen hverdag.
1	Utvecklare	Proactive Gaming	4	4	2016-11-01	
2	Systemutvecklare	Briljant (via Academic Work)	4	4	2016-12-10	
318	Web Developer	IKEA e-Commerce Norway	34	1	2018-01-31	Det som motiverer meg er det å jobbe for et stort multinasjonalt firma som IKEA. Jeg motiveres generelt sett av det å jobbe med gode, kompetente kollegaer. Selv om jeg ikke er en ledertype, syns jeg det viker spennende å påvirke min egen hverdag.
\.


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
22	Tønsberg	1
23	Tysvær	1
24	Sandefjord	1
25	Askim	1
26	Lindesnes	1
27	Jessheim	1
28	Asker	1
29	Tjøme	1
30	Stavanger	1
31	Leikanger	1
32	Trondheim	1
33	Kristiansund	1
34	Billingstad	1
\.


--
-- Name: landid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('landid_seq', 3, true);


--
-- Name: soknadid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('soknadid_seq', 318, true);


--
-- Name: statusid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('statusid_seq', 8, true);


--
-- Name: stedid_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('stedid_seq', 34, true);


--
-- Name: user_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('user_id_seq', 1, false);


--
-- Name: land land_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY land
    ADD CONSTRAINT land_pkey PRIMARY KEY (landid);


--
-- Name: soknad soknad_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_pkey PRIMARY KEY (soknadid);


--
-- Name: status status_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY status
    ADD CONSTRAINT status_pkey PRIMARY KEY (statusid);


--
-- Name: sted sted_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT sted_pkey PRIMARY KEY (stedid);


--
-- Name: soknad unik_soknad; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT unik_soknad UNIQUE (tittel, bedrift, stedid);


--
-- Name: status unik_status; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY status
    ADD CONSTRAINT unik_status UNIQUE (status);


--
-- Name: land unikt_land; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY land
    ADD CONSTRAINT unikt_land UNIQUE (land);


--
-- Name: sted unikt_sted; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT unikt_sted UNIQUE (stedsnavn);


--
-- Name: soknad trg_nysoknad; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nysoknad AFTER INSERT ON soknad FOR EACH ROW EXECUTE PROCEDURE nysoknadid();


--
-- Name: land trg_nyttland; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nyttland AFTER INSERT ON land FOR EACH ROW EXECUTE PROCEDURE nylandid();


--
-- Name: sted trg_nyttsted; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_nyttsted AFTER INSERT ON sted FOR EACH ROW EXECUTE PROCEDURE nystedid();


--
-- Name: soknad trg_oppdatersoknad; Type: TRIGGER; Schema: public; Owner: andersbo
--

CREATE TRIGGER trg_oppdatersoknad AFTER UPDATE ON soknad FOR EACH ROW EXECUTE PROCEDURE updatesoknad();


--
-- Name: soknad soknad_statusid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_statusid_fkey FOREIGN KEY (statusid) REFERENCES status(statusid);


--
-- Name: soknad soknad_stedid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY soknad
    ADD CONSTRAINT soknad_stedid_fkey FOREIGN KEY (stedid) REFERENCES sted(stedid);


--
-- Name: sted sted_landid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY sted
    ADD CONSTRAINT sted_landid_fkey FOREIGN KEY (landid) REFERENCES land(landid);


--
-- PostgreSQL database dump complete
--


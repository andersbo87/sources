--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: tbl_bedrift; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_bedrift (
    bedriftsid integer NOT NULL,
    bedriftsnavn character varying(25) NOT NULL,
    postnr integer NOT NULL
);


ALTER TABLE public.tbl_bedrift OWNER TO andersbo;

--
-- Name: tbl_jobb; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_jobb (
    jobbid integer NOT NULL,
    stillingsnavn character varying(25) NOT NULL,
    bedriftsid integer NOT NULL,
    statusid integer NOT NULL,
    soknadsfrist character(10) NOT NULL,
    personid integer NOT NULL,
    beskrivelse character varying(10000000) NOT NULL
);


ALTER TABLE public.tbl_jobb OWNER TO andersbo;

--
-- Name: tbl_kontaktperson; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_kontaktperson (
    personid integer NOT NULL,
    navn character varying(50) NOT NULL,
    e_post character varying(50),
    mobilnr character varying(15)
);


ALTER TABLE public.tbl_kontaktperson OWNER TO andersbo;

--
-- Name: tbl_postnr_sted; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_postnr_sted (
    postnr integer NOT NULL,
    poststed character varying(25) NOT NULL
);


ALTER TABLE public.tbl_postnr_sted OWNER TO andersbo;

--
-- Name: tbl_status; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_status (
    statusid integer NOT NULL,
    status character varying(20) NOT NULL
);


ALTER TABLE public.tbl_status OWNER TO andersbo;

--
-- Name: qry_jobb; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW qry_jobb AS
    SELECT tbl_jobb.jobbid, tbl_jobb.stillingsnavn, tbl_jobb.bedriftsid, tbl_bedrift.bedriftsnavn, tbl_bedrift.postnr, tbl_postnr_sted.poststed, tbl_jobb.personid, tbl_kontaktperson.navn, tbl_kontaktperson.e_post, tbl_kontaktperson.mobilnr, tbl_jobb.soknadsfrist, tbl_jobb.statusid, tbl_status.status FROM tbl_jobb, tbl_bedrift, tbl_kontaktperson, tbl_postnr_sted, tbl_status WHERE ((((tbl_jobb.bedriftsid = tbl_bedrift.bedriftsid) AND (tbl_jobb.personid = tbl_kontaktperson.personid)) AND (tbl_bedrift.postnr = tbl_postnr_sted.postnr)) AND (tbl_jobb.statusid = tbl_status.statusid));


ALTER TABLE public.qry_jobb OWNER TO andersbo;

--
-- Name: qry_jobb_beskrivelse; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW qry_jobb_beskrivelse AS
    SELECT tbl_jobb.jobbid, tbl_jobb.stillingsnavn, tbl_jobb.beskrivelse, tbl_jobb.bedriftsid, tbl_bedrift.bedriftsnavn, tbl_bedrift.postnr, tbl_postnr_sted.poststed, tbl_jobb.personid, tbl_kontaktperson.navn, tbl_kontaktperson.e_post, tbl_kontaktperson.mobilnr, tbl_jobb.soknadsfrist, tbl_jobb.statusid, tbl_status.status FROM tbl_jobb, tbl_bedrift, tbl_kontaktperson, tbl_postnr_sted, tbl_status WHERE ((((tbl_jobb.bedriftsid = tbl_bedrift.bedriftsid) AND (tbl_jobb.personid = tbl_kontaktperson.personid)) AND (tbl_bedrift.postnr = tbl_postnr_sted.postnr)) AND (tbl_jobb.statusid = tbl_status.statusid));


ALTER TABLE public.qry_jobb_beskrivelse OWNER TO andersbo;

--
-- Data for Name: tbl_bedrift; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_bedrift (bedriftsid, bedriftsnavn, postnr) FROM stdin;
1	Nets AS	978
2	Visma Personell AS	1624
3	Experis	0
\.


--
-- Data for Name: tbl_jobb; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_jobb (jobbid, stillingsnavn, bedriftsid, statusid, soknadsfrist, personid, beskrivelse) FROM stdin;
1	Systemadministrator	1	1	Snarest   	1	Platform Servers består av 22 medarbeidere, og er lokalisert både i Oslo og København. Vi ønsker nå å styrke vårt driftsteam i Norge og søker derfor nye medarbeidere. Platform Servers har ansvar for driften av høy-sikkerhetstjenester og søker dyktige personer som kan bidra til å sikre en stabil og sikker drift av disse tjenestene. Vi satser tungt på virtualisering og benytter vmware som virtualiseringsteknologi. Tjenestene kjører på Linux (SLES)/Solaris/Windows. Du vil være med å bidra til at plattformen har nødvendig stabilitet og ytelse og sørge for at vi leverer tjenester på en smidig og effektiv måte. Du vil få følgende ansvarsområder: *Drift og vedlikehold av unix plattformen **Vmware **Linux/Solaris **Weblogic/Jboss **Tomcat **Apache *Nye installasjoner, samt oppgraderinger av eksisterende løsninger *Backup/recovery løsninger *Tuning og ytelsesoptimalisering *Drift og forvaltning av hardware plattformen. Du har følgende formelle kompetanse og erfaring: *Høyskole eller universitetsutdannelse, eventuelt relevant praksis *God kompetanse på operativsystemet Linux/Solaris *Erfaring med datasenter drift og kunnskap om infrastruktur-løsninger på distribuerte miljøer *Norsk muntlig og skrifltig er et krav. Følgende personlige egenskaper vektlegges: *Analytisk og er god til å finne løsninger  *Positiv, drivende person med gode kommunikasjonsevner *Setter deg raskt inn i nye teknologier *Selvstendig og strukturert *Høy gjennomføringsevne. Vi kan tilby deg: * Konkurransedyktige betingelser, inkludert gode pensjons- og forsikringsordninger *En spennende stilling med krevende og sentrale oppgaver i selskapet *Mulighet for faglig og personlig vekst, og stor grad av frihet og selvledelse *Gode kolleger i et arbeidsmiljø kjennetegnet av kompetanse, trivsel, samspill og en uformell tone *Et bredt spekter av sportslige, kulturelle og sosiale tilbud
2	IT-systemutviklere	2	2	Snarest   	2	Ønsker en som har erfaring innen *)Utvikling i C# .NET eller Java *) kan bruke "ny" teknologi som Visual Studio og SQL Server, Biztalk, etc *) Enterprise arkitektur og SOA.
3	Junior .NET utvikler	3	1	Snarest   	3	Junior .net-utvikler\nVi søker etter nyutdannede teknologer innen systemutvikling eller junior systemutviklere med 3 års erfaring.\nDu vil inngå i et team med erfarne systemutviklere med inngående kjennskap til applikasjonene. Applikasjonene er basert på MS-tenkologi, du vil i hovedsak jobbe med utvikling i C# .net. Du vil jobbe på alle nivå i applikasjonen, både front end med en del grafisk fremstilling av data, på forretningslaget med en komplisert logikk og databaselaget. Målet er at du på sikt skal utvikle deg til å bli en stødig og allsidig systemutvikler. \n\nKvalifikasjoner\n\nDu er helt nyutdannet eller har jobbet noen år med systemutvikling\nUtdanning på Master- eller Bachelornivå, helst med spesialisering innen systemutvikling.\nFordel med gode karakterer innen fag relatert til systemutvikling\nGod muntlig og skriftlig fremstillingsevne (norsk og engelsk)\nPersonlige egenskaper\n\nDu trives i team men kan også selv ta initiativ til oppgaver\nDu er nysgjerrig på teknologi\nDu har interesse og evne til å se feil og løsninger\nDu ønsker å ha en bratt læringskurve\nDu er interessert i å lære mer om Microsofts produkter
\.


--
-- Data for Name: tbl_kontaktperson; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_kontaktperson (personid, navn, e_post, mobilnr) FROM stdin;
1	Rodi Kristiansen	\N	92063463
2	Walther Spro	walther.spro@visma.no	41206091
3	Astri Morgan-Smith	Astri.Morgan-Smith@no.experis.com	+4792698683
\.


--
-- Data for Name: tbl_postnr_sted; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_postnr_sted (postnr, poststed) FROM stdin;
1713	\\x5361727073
1720	Sarps
1712	Grål
978	Oslo
1624	Gressvik
0	Ukjent sted
\.


--
-- Data for Name: tbl_status; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_status (statusid, status) FROM stdin;
1	Registrert
2	Søknad sendt
3	Intervju
4	Ikke interessert
5	Kanskje
\.


--
-- Name: tbl_bedrift_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_bedrift
    ADD CONSTRAINT tbl_bedrift_pkey PRIMARY KEY (bedriftsid);


--
-- Name: tbl_jobb_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_jobb
    ADD CONSTRAINT tbl_jobb_pkey PRIMARY KEY (jobbid);


--
-- Name: tbl_kontaktperson_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_kontaktperson
    ADD CONSTRAINT tbl_kontaktperson_pkey PRIMARY KEY (personid);


--
-- Name: tbl_postnr_sted_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_postnr_sted
    ADD CONSTRAINT tbl_postnr_sted_pkey PRIMARY KEY (postnr);


--
-- Name: tbl_status_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_status
    ADD CONSTRAINT tbl_status_pkey PRIMARY KEY (statusid);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--


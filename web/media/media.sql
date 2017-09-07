--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.3
-- Dumped by pg_dump version 9.6.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

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
-- Name: film_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE film_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE film_id_seq OWNER TO andersbo;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: film; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE film (
    filmnr integer DEFAULT nextval('film_id_seq'::regclass) NOT NULL,
    filmnavn text NOT NULL,
    serienr integer NOT NULL,
    typenr integer NOT NULL,
    lengde character varying(10) NOT NULL,
    filbane text NOT NULL,
    beskrivelse text
);


ALTER TABLE film OWNER TO andersbo;

--
-- Name: TABLE film; Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON TABLE film IS 'Tabell med diverse ulike egenskaper om filmen:
FilmNr,
Tittel,
SerieNr,
TypeNr,
Lengde
Filbane
Beskrivelse';


--
-- Name: filmtype; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE filmtype (
    typenr integer NOT NULL,
    typenavn text
);


ALTER TABLE filmtype OWNER TO andersbo;

--
-- Name: TABLE filmtype; Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON TABLE filmtype IS 'Tabell med ulike filmtyper: "Ingen type", "Let''s Play" og "Feriefilmer"';


--
-- Name: COLUMN filmtype.typenr; Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON COLUMN filmtype.typenr IS 'ID-en til filmtypen';


--
-- Name: COLUMN filmtype.typenavn; Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON COLUMN filmtype.typenavn IS 'Navnet på filmtypen';


--
-- Name: serie; Type: TABLE; Schema: public; Owner: andersbo
--

CREATE TABLE serie (
    serienr integer NOT NULL,
    serienavn text NOT NULL,
    typenr integer,
    seriebeskrivelse text
);


ALTER TABLE serie OWNER TO andersbo;

--
-- Name: TABLE serie; Type: COMMENT; Schema: public; Owner: andersbo
--

COMMENT ON TABLE serie IS 'Tabell med de ulike seriene.';


--
-- Name: view_film; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW view_film AS
 SELECT film.filmnr,
    film.filmnavn,
    serie.serienavn,
    filmtype.typenavn,
    film.lengde,
    film.beskrivelse,
    film.filbane
   FROM ((film
     JOIN serie ON ((serie.serienr = film.serienr)))
     JOIN filmtype ON ((film.typenr = filmtype.typenr)));


ALTER TABLE view_film OWNER TO andersbo;

--
-- Data for Name: film; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY film (filmnr, filmnavn, serienr, typenr, lengde, filbane, beskrivelse) FROM stdin;
10	Quantum Break del 10	1	1	1:15:25	/quantum_break/quantum_break_del10.mp4	Den tiende delen av min gjennomgang av spillet Quantum Break.
11	Quantum Break del 11	1	1	1:08:58	/quantum_break/quantum_break_del11.mp4	Den ellevte delen av min gjennomgang av spillet Quantum Break.
1	Quantum Break del 01	1	1	1:57:43	/quantum_break/quantum_break_del1.mp4	Første del av spillserien "Quantum Break".
2	Quantum Break del 02	1	1	2:45:57	/quantum_break/quantum_break_del2.mp4	Den andre delen av min gjennomgang av spillet Quantum Break.
3	Quantum Break del 03	1	1	52:27	/quantum_break/quantum_break_del3.mp4	Tredje del av min gjennomgang av spillet Quantum Break.
4	Quantum Break del 04	1	1	1:12:44	/quantum_break/quantum_break_del4.mp4	Fjerde del av min gjennomgang av spillet Quantum Break
5	Quantum Break del 05	1	1	34:04	/quantum_break/quantum_break_del5.mp4	Den femte delen av min gjennomgang av spillet Quantum Break
6	Quantum Break del 06	1	1	38:07	/quantum_break/quantum_break_del6.mp4	Den sjette delen av min gjennomgang av spillet Quantum Break.
7	Quantum Break del 07	1	1	58:53	/quantum_break/quantum_break_del7.mp4	Den syvende delen av min gjennomgang av spillet Quantum Break.
8	Quantum Break del 08	1	1	31:51	/quantum_break/quantum_break_del8.mp4	Den åttende delen av min gjennomgang av spillet Quantum Break.
9	Quantum Break del 09	1	1	1:38:32	/quantum_break/quantum_break_del9.mp4	Den niende delen av min gjennomgang av spillet Quantum Break.
25	Rise of the Tomb Raider del 10	3	1	49:40	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del10.mp4	Lara er tilbake i Geothermal Valley etter et dramatisk møte med Trinity i den forrige episoden. Dette er først og fremst en episode hvor utforskning står i fokus, selv om det også i denne episoden er et møte med soldater fra Trinity.
38	Assassins Creed Syndicate del 10: Unnatural Selection	4	1	29:58	/ac_syndicate/ac_syndicate_del10.mp4	Jacob fortsetter søket etter personen som lagde Starricks Soothing Syrup ved å spore sirupen tilbake til desilleriet.
39	Assassins Creed Syndicate del 11: On the Origin of Syrup	4	1	3:19	/ac_syndicate/ac_syndicate_del11.mp4	Jacob forbereder seg på å infiltrere asylmottaket for å avsløre personen som står bak Starricks Soothing Syrup. Oppdragets tittel er kanskje et ordspill på "On the Origin of Species"?
26	Rise of the Tomb Raider del 11	3	1	1:16:09	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del11.mp4	En utforskningsbasert episode som finner sted i den sovjetiske installasjonen. Lara løser en utfordring som går ut på å kutte ned et antall sovjetiske flagg, og hun besøker også graven Voice of God.
27	Rise of the Tomb Raider del 12	3	1	1:44:39	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del12.mp4	Lara får seg en spennende og våt opplevelse i Flooded Archive.
28	Rise of the Tomb Raider del 13	3	1	12:20	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del13.mp4	En kort 12-minutters episode som finner sted i Geothermal Valley hvor Lara plukker opp ting som ble oversett i tidligere episoder.
13	Assassins Creed Syndicate del 02	4	1	19:39	/ac_syndicate/ac_syndicate_del02.mp4	Søskenparet ankommer London, hvor de møter Henry Green. Jacob starter opp en gjeng kalt "The Rooks", etter en sjakkbrikke med samme engelske navn (tårn på norsk)
14	Assassins Creed Syndicate del 03	4	1	51:09	/ac_syndicate/ac_syndicate_del03.mp4	Evie begynner på oppgaven med å frigjøre Whitechapel fra klørne til The Blighters. Vi møter på Clara O Dea som forklarer hvordan nevnte gjeng driver på med ulovlig barnearbeid, med mer.
15	Assassins Creed Syndicate del 04	4	1	18:36	/ac_syndicate/ac_syndicate_del04.mp4	Søskenparet får utlevert et verktøy for å lage sine egne "zip lines" som gjør at de raskt kan bevege seg fra tak til tak. Evie hjelper Alexander Graham Bell med en tjeneste.
37	Assassins Creed Syndicate del 09: A Spoonful of Syrup	4	1	26:05	/ac_syndicate/ac_syndicate_del09.mp4	Jacob etterforsker et nytt narkotikum som ødelegger London. Målet for etterforskningen er å finne ut hvem som står bak.
17	Rise of the Tomb Raider del 02	3	1	1:02:14	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del2.mp4	Lara kommer til den sibirske villmarken hvor hun på nytt møter fienden Trinity og må bekjeme en bjørn for å komme videre…
18	Rise of the Tomb Raider del 03	3	1	1:44:58	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del3.mp4	Lara kommer frem til det første store stedet i spillet, en sovjetisk installasjon. I denne episoden er det først og fremst mye frivillig utforskning, blant annet besøker vi en gammel sisterne.
19	Rise of the Tomb Raider del 04	3	1	1:00:02	/rise_of_the_tomb_riader/Rise_of_the_Tomb_Raider_del4.mp4	Ferden gjennom den sovjetiske installasjonen fortsetter. I denne episoden møter Lara på en alliert med navn Jacob, som vi følger gjennom store deler av spillet. De to må lære seg å samarbeide for å kunne slippe ut av et fengsel de havner inn i.
20	Rise of the Tomb Raider del 05	3	1	52:10	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del5.mp4	Nok en utforskningsbasert episode som ført og fremst fokuserer på området rundt fengselet i den sovjetiske installasjonen.
21	Rise of the Tomb Raider del 06	3	1	2:29:11	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del6.mp4	Jacob og Lara foretar en dramatisk flukt gjennom ei forlatt gruve og kommer til slutt fram til Jacobs landsby i Geothermal valley. Noe utforskning blir det også her; vi besøker blant annet Den røde gruva, som er et  av flere gravsteder i den sovjetiske installasjonen.
22	Rise of the Tomb Raider del 07	3	1	1:09:21	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del7.mp4	Lara utforsker Geothermal Valley, gjennomfører et oppdrag for en venn og besøker gravstedet House of the Afflicted.
23	Rise of the Tomb Raider del 08	3	1	52:49	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del8.mp4	I denne episoden utforsker Lara landsbyen i Geothermal Valley, i tillegg til å fullføre et par "utfordringer".
24	Rise of the Tomb Raider del 09	3	1	2:11:44	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del9.mp4	Denne episoden tar oss blant annet til The Acropolis hvor nok et dramatisk møte med fienden Trinity venter for Lara.
29	Rise of the Tomb Raider del 14	3	1	57:46	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del14.mp4	Lara besøker graven The Pit of Judgement i Geothermal Valley, før hun fullfører den siste utfordringen i området. Til slutt finner hun ut av hvor den forsvunnede byen er, og Jonah blir tatt til fange.
30	Rise of the Tomb Raider del 15	3	1	1:15:37	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del15.mp4	Lara bestemmer seg for å forsøke å redde Jonah, noe hun på sett og vis klarer, men ikke helt uten konsekvenser.
31	Rise of the Tomb Raider del 16	3	1	1:44:24	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del16.mp4	Lara forlater Geothermal Valley og begynner ferden mot Kitezh. Hun beveger seg gjennom et tellurium og deretter tar hun seg gjennom "De dødløses sti" før hun til slutt kommer frem til den skjulte byen, hvor hun blant annet besøker spillets siste gravsted.
32	Rise of the Tomb Raider del 17: Finale	3	1	1:30:53	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del17.mp4	Lara fortsetter ferden gjennom- og etter hvert ut av den "skjulte" byen. Spillets siste, dramatiske møte med Trinity finner sted, og vi får også vite hva som til slutt skjer med Ana.
60	Assassins Creed Syndicate del 32: One Good Deed	4	1	9:42	/ac_syndicate/ac_syndicate_del32.mp4	Evie besøker Southwark etter at Jacob myrdet Pearl og stenger omnibusselskapet hennes.
61	Assassins Creed Syndicate del 33: A Bad Penny	4	1	12:04	/ac_syndicate/ac_syndicate_del33_twopenny_assassination_bank_of_england.mp4	Jacob forbereder seg på å gå inn i Bank of England, stoppe ranet og eliminere Twopenny.
62	Assassins Creed Syndicate del 34: Change of Plans	4	1	20:51	/ac_syndicate/ac_syndicate_del34.mp4	Evies søken etter "The Shroud of Eden" får en ny utvikling.
63	Assassins Creed Syndicate del 35: Karl Marx 1: Cat and Mouse	4	1	13:46	/ac_syndicate/ac_syndicate_del35_karl_marx1.mp4	Marx får hjelp til å unngå London-politiet.
64	Assassins Creed Syndicate del 36: Karl Marx 2: Anarchist Intervention	4	1	5:28	/ac_syndicate/ac_syndicate_del36_karl_marx2.mp4	En sørgende arbeider planlegger en revansje som involverer noen tempelriddereksplosiver. Mannen må stoppes før noen blir skadet
65	Assassins Creed Syndicate del 37: Karl Marx 3: Where There is Smoke	4	1	5:28	/ac_syndicate/ac_syndicate_del37_karl_marx3.mp4	Evie finner bevis for at en fabrikk misbruker arbeidsstyrken.
66	Assassins Creed Syndicate del 38: Karl Marx 4: An Explosive End	4	1	7:02	/ac_syndicate/ac_syndicate_del38_karl_marx4.mp4	Frank Morris har funnet tempelriddernes eksplosiver og nekter å gi seg før han får tak i disse eksplosivene.
67	Assassins Creed Syndicate del 39: Karl Marx 4: Vox Populi	4	1	10:01	/ac_syndicate/ac_syndicate_del39_karl_marx5.mp4	Karl Marx beskyttes mens han holder en tale.
68	Assassins Creed Syndicate del 40: Charles Dickens 1: Hells Bells 	4	1	12:47	/ac_syndicate/ac_syndicate_del40_charles_dickens1.mp4	Finn ut av sannheten bake noen paranormale tyverier.
69	Assassins Creed Syndicate del 41: Charles Dickens 2: Recollection	4	1	11:05	/ac_syndicate/ac_syndicate_del41_charles_dickens2.mp4	"The Ghost Club" etterforsker omstendighetene som førte til at den forvirrede snikmorderen ble arrestert.
70	Assassins Creed Syndicate del 42: Charles Dickens 3: 50 Berkeley Square	4	1	8:09	/ac_syndicate/ac_syndicate_del42_charles_dickens3.mp4	Evie etterforsker Londons mest hjemsøkte hus.
71	Assassins Creed Syndicate del 43: Charles Dickens 4: Dead Letters	4	1	5:23	/ac_syndicate/ac_syndicate_del43_charles_dickens4.mp4	Mens Evie etterforsker en hjemsøkt vogn, får en sliten snikmorder et personlig brev fra en fremmed.
59	Assassins Creed Syndicate del 31: A Thorne in the Side	4	1	28:42	/ac_syndicate/ac_syndicate_del31.mp4	Evie og Henry søker i bøkene deres etter en illustrasjon av nøkkelen som ble stjålet av Miss Thorne.
57	Assassins Creed Syndicate del 29: Første verdenskrig 2	4	1	26:21	/ac_syndicate/ac_syndicate_del29.mp4	Den andre delen i den delen av spillet som omhandler den første verdenskrig i London.
43	Assassins Creed Syndicate del 15: Train Hideout: Stalk the Stalker	4	1	14:41	/ac_syndicate/ac_syndicate_del15.mp4	Evie lurer Agnes stalker tilbake til toget.
41	Assassins Creed Syndicate del 13: The Crate Escape	4	1	12:23	/ac_syndicate/ac_syndicate_del13.mp4	Evie har funnet ut av hvor tempelriddernes "Piece of Eden" befinner seg (01:08). Før dette møter Evie på Robert Topping.
42	Assassins Creed Syndicate del 14: Playing it by Ear	4	1	19:48	/ac_syndicate/ac_syndicate_del14.mp4	Evies søk etter "The Piece of Eden" fortsetter ved at hun undersøker notisboka som ble funnet i Miss Thornes kiste.
44	Assassins Creed Syndicate del 16	4	1	11:52	/ac_syndicate/ac_syndicate_del16.mp4	Diverse klipp fra noe "free roaming", avsluttende cutscene med Ned Wynert og Evie henter en helt ny klesdrakt.
45	Assassins Creed Syndicate del 17: Overdose	4	1	26:35	/ac_syndicate/ac_syndicate_del17.mp4	Jacob infiltrerer det mystiske asylmottaket i Lambeth for å ta Dr. Elliotson av dage.
46	Assassins Creed Syndicate del 18: Breaking News	4	1	13:00	/ac_syndicate/ac_syndicate_del18.mp4	Evie og Jacob besøker Bell i laboratoriet hans for å fortsette kampen mot Starrick og den kontrollen han har over pressen.
47	Assassins Creed Syndicate del 19: The Lady with the Lamp	4	1	8:55	/ac_syndicate/ac_syndicate_del19.mp4	Evie besøker Lambeth etter at Jacob myrdet Dr. Elliotson.
48	Assassins Creed Syndicate del 20	4	1	7:22	/ac_syndicate/ac_syndicate_del20.mp4	Evie jakter på "The Spring-heeled Jack"
49	Assassins Creed Syndicate del 21: Train Hideout 2: Nigel in for the Chop	4	1	14:29	/ac_syndicate/ac_syndicate_del21.mp4	Evie hjelper til med å få Nigel frikjent ved å ødelegge bevisene mot ham.
51	Assassins Creed Syndicate del 23: Train Hideout 5: A Long Night & Friendly Competition	4	1	20:42	/ac_syndicate/ac_syndicate_del23.mp4	"A Long Night": Jacob finner en lærling og tar ham trygt med tilbake til gjemmestedet i toget. "Friendly Competition": Jacob introduserer seg til Perl Attaway, hovedkonkurrenten til Starricks omnibusselskap som eies av Malcolm Millner.
33	Assassins Creed Syndicate del 05	4	1	10:29	/ac_syndicate/ac_syndicate_del05.mp4	Evie gjennomfører oppdrag for å frigjøre en bydel i London fra The Blighters. 
34	Assassins Creed Syndicate del 06	4	1	15:45	/ac_syndicate/ac_syndicate_del06.mp4	Kort fortalt er dette en fortsettelse av det forrige klippet.
35	Assassins Creed Syndicate del 07	4	1	3:38	/ac_syndicate/ac_syndicate_del07.mp4	Evie gjennomfører en "Child Liberation".
52	Assassins Creed Syndicate del 24: Research and Development	4	1	12:03	/ac_syndicate/ac_syndicate_del24.mp4	Jacob besøker Miss Attaway igjen for å fortsette angrepet mot Millner.
53	Assassins Creed Syndicate del 25: Survival of the Fittest	4	1	12:28	/ac_syndicate/ac_syndicate_del25.mp4	Jacob og Pearl har nesten ødelagt Millners forretning. Det er bare én ting til som må gjøres...
54	Assassins Creed Syndicate del 26: A Room with a Wiew	4	1	15:50	/ac_syndicate/ac_syndicate_del26.mp4	Evie finner spor som fører henne nærmere "The Piece of Eden".
55	Assassins Creed Syndicate del 27: End of the Line	4	1	21:42	/ac_syndicate/ac_syndicate_del27.mp4	Jacob drar til Waterloo Station for å ta tilbake lokomotivene og eliminere Pearl Attaway, som er blitt avslrt som en tempelridder.
56	Assassins Creed Syndicate del 28: Første verdenskrig 1	4	1	22:35	∕ac_syndicate/ac_syndicate_del28.mp4	Den første delen i den delen av spillet som omhandler den første verdenskrig i London.
58	Assassins Creed Syndicate del 30: A Case of Identity & A Spot of Tea	4	1	18:11	/ac_syndicate/ac_syndicate_del30.mp4	"A Case of Identity": Jacob tenker å jakte på Mr. Dredge for å avsløre Plutus. "A Spot of Tea": Jacob planlegger å følge våpenboksene til Cockham til ankomststedet for å avdekke Plutus, mannen som planlegger bankranet.
40	Assassins Creed Syndicate del 12: Cable News	4	1	21:16	/ac_syndicate/ac_syndicate_del12.mp4	Jacob og Evie besøker Alexander Graham Bell og lærer noe helt nytt (fra 05:50). Før dette deltar Evie i et gjengoppgjør.
50	Assassins Creed Syndicate del 22: Train Hideout 3: Hullo Mr. Gatling og Train Hideout 4: Runaway Train	4	1	14:18	/ac_syndicate/ac_syndicate_del22.mp4	"Hullo, Mr. Gatling": Jacob forsvarer toget mot angrep med hjelp av en Gatling-gun. "Runaway Train": Evie må skynde seg å reparere et løpsk tog før det sporer av.
72	Assassins Creed Syndicate del 44: Charles Dickens 5: The Terror of London	4	1	7:26	/ac_syndicate/ac_syndicate_del44_charles_dickens5.mp4	Spring-Heeled Jack kommer tilbake for å plage Londons innbyggere og må stoppes.
73	Assassins Creed Syndicate del 45: Charles Darwin 1: The Berlin Specimen	4	1	11:28	/ac_syndicate/ac_syndicate_del45_charles_darwin1.mp4	Evie må beskytte en kollega av Darwin og hente et verdifullt fossil.
74	Assassins Creed Syndicate del 46: Charles Darwin 2: An Abominable Mystery	4	1	8:24	/ac_syndicate/ac_syndicate_del46_charles_darwin2.mp4	Evie etteforsker en rar blomst som har dukket opp i London.
75	Assassins Creed Syndicate del 47: Charles Darwin 3: Defamation	4	1	3:49	/ac_syndicate/ac_syndicate_del47_charles_darwin3.mp4	Evie må hente en avis til Darwin.
76	Assassins Creed Syndicate del 48: Charles Darwin 4: Cruel Caricature	4	1	13:19	/ac_syndicate/ac_syndicate_del48_charles_darwin4.mp4	Evie leter etter kilden for propagandaen mot Charles Darwin
77	Assassins Creed Syndicate del 49: Charles Darwin 5: A Struggle for Existence	4	1	11:19	/ac_syndicate/ac_syndicate_del49_charles_darwin5.mp4	Darwin må reddes før det er for sent.
78	Assassins Creed Syndicate del 50: Darwin and Dickens Conspiracy: Darwins Orchid	4	1	4:09	/ac_syndicate/ac_syndicate_del50_darwin_and_dickens_conspiracy1.mp4	Få tilbake Darwins orkidé ved havna.
79	Assassins Creed Syndicate del 51: Darwin and Dickens Conspiracy: Our Mutual Friend	4	1	8:48	/ac_syndicate/ac_syndicate_del51_darwin_and_dickens_conspiracy2.mp4	Hils på en venn av Mr. Dickens og Mr. Darwin.
80	Assassins Creed Syndicate del 52: Darwin and Dickens Conspiracy: An Artful Plan	4	1	11:18	/ac_syndicate/ac_syndicate_del52_darwin_and_dickens_conspiracy3.mp4	Hjelp John Hammon med å vinne ei jentes hjerte.
81	Assassins Creed Syndicate del 53: Dreadful Crimes 1: A Simple Matter of Murder!	4	1	17:42	/ac_syndicate/ac_syndicate_del53_dreadful_crimes1.mp4	Evie må løse det som ser ut til å være et enkelt mord av en fabrikkarbeider.
12	Assassins Creed Syndicate del 01	4	1	01:09:40	/ac_syndicate/ac_syndicate_del01.mp4	Første del av spillet hvor søskenparet, etter noe om og men, bestemmer seg for å ta seg til London.
36	Assassins Creed Syndicate del 08	4	1	12:31	/ac_syndicate/ac_syndicate_del08.mp4	Evie og Jacob møter på den allierte personen Ned Wynert før Evie gjennomfører en "Cargo Highjack"
82	Assassins Creed Syndicate del 54: Dreadful Crimes 2: Death Stalks the Colonoel	4	1	17:53	/ac_syndicate/ac_syndicate_del54_dreadful_crimes2.mp4	Evie må avgjøre hvilken kule det var som traff og traff obersten.
83	Assassins Creed Syndicate del 55: Dreadful Crimes 3: The Case of the Conflicted Courtship	4	1	27:01	/ac_syndicate/ac_syndicate_del55_dreadful_crimes3.mp4	Evie må løse mordet mot ei dame i en offentlig park.
84	Assassins Creed Syndicate del 56: Dreadful Crimes 4: The Mystery of the Twice-Dead Professor	4	1	21:38	/ac_syndicate/ac_syndicate_del56_dreadful_crimes4.mp4	Evie må løse mysteriet om professoren som først ble begravd, for så å dø i sin egen hage.
85	Assassins Creed Syndicate del 57: Dreadful Crimes 5: The Fiend of Fleet Street	4	1	19:23	/ac_syndicate/ac_syndicate_del57_dreadful_crimes5.mp4	Evie må løse saken om den savnede Detective Murphy.
86	Assassins Creed Syndicate del 58: Dreadful Crimes 6: Locked in to Die	4	1	23:45	/ac_syndicate/ac_syndicate_del58_dreadful_crimes6.mp4	Evie må løse et mord som fant sted inne i et låst rom.
87	Assassins Creed Syndicate del 59: Dreadful Crimes 7: The Most Hated Man in London	4	1	21:56	/ac_syndicate/ac_syndicate_del59_dreadful_crimes7.mp4	Evie må finne ut av hvem av de potensielle morderne som faktisk tok livet av Ashton.
88	Assassins Creed Syndicate del 60: Dreadful Crimes 8: Conjuring up a Killing!	4	1	37:59	/ac_syndicate/ac_syndicate_del60_dreadful_crimes8.mp4	Evie må løse mordet av den åndelige Thaddeus the Amazing.
89	Assassins Creed Syndicate del 61: Dreadful Crimes 9: Next Stop: Murder!	4	1	23:09	/ac_syndicate/ac_syndicate_del61_dreadful_crimes9.mp4	Evie løser mysteriet om et lik som blir funnet langs Themsens bredder.
90	Assassins Creed Syndicate del 62: Dreadful Crimes 10: Murder at the Palace!	4	1	31:19	/ac_syndicate/ac_syndicate_del62_dreadful_crimes10.mp4	Evie løser mysteriet med et mord på én av vaktene ved Buckingham Palace.
91	Assassins Creed Syndicate del 63: Duleep Singh 1: A Good Shot	4	1	11:29	/ac_syndicate/ac_syndicate_del63_duleep_singh1.mp4	Henry ber Jacob og Evie om å møte ham under en parkfest som holdes i en park ved Buckingham Palace. Når snikmorderne ankommer festen, krangler Henry og Duleep Singh, Indias siste maharaja, om forfliktelsene over det indiske folk.
92	Assassins Creed Syndicate del 64: Duleep Singh 2: Information Intercepted	4	1	11:22	/ac_syndicate/ac_syndicate_del64_duleep_singh2.mp4	For å få Duleep til å forstå hvor viktig han er for Indias fremtid ber Henry snikmorderne om å bevise at Duleep har fått munnkurv av gitte personer. For å kunne gjøre det må Jacob og Evie finne Duleeps stjålne brev og gi dem tilbake til ham.
93	Assassins Creed Syndicate del 65: Duleep Singh 3: Stealing from the Poor	4	1	10:23	/ac_syndicate/ac_syndicate_del65_duleep_singh3.mp4	Duleep oppdager at det finnes en iverksatt plan for å donere stjålne indiske Punjabi-rikdommer til det britiske østindiske kompanis organisasjon. Denne transaksjonen må stoppes. Disse rikdommene må returneres til India.
94	Assassins Creed Syndicate del 66: Duleep Singh 4: A Golden Path	4	1	09:56	/ac_syndicate/ac_syndicate_del66_duleep_singh4.mp4	Etter å ha oppdaget hvor det stjålne gullet er, legger Duleep og snikmorderne ut på et oppdrag for å finne det.
95	Assassins Creed Syndicate del 67: Duleep Singh 5: A Good Send-Off	4	1	15:20	/ac_syndicate/ac_syndicate_del67_duleep_singh5.mp4	Hver uke kommer det båter som er fulle av stjålne indiske rikdommer til Londons havner. I det gullet lastes ombord i båten til en betrodd alliert, møtes Duleep og snikmorderne ansikt til ansikt med tempelridderne, noe som leder til et siste "slag" før forsendelsen ledes ut av engelsk farvann.
96	Assassins Creed Syndicate del 68: Duleep Singh 6: Off the Rails	4	1	10:47	/ac_syndicate/ac_syndicate_del68_duleep_singh6.mp4	Etter at sagaen om rikdommene er over, er Duleep klar for å sette en annen plan i sving. Han ber om et møte med snikmorderne for en briefing.
97	Assassins Creed Syndicate del 69: Duleep Singh 7: Much Ado about Drinking	4	1	15:21	/ac_syndicate/ac_syndicate_del69_duleep_singh7.mp4	Etter "The Great Train Debaucle" avslører Duleep endelig idéen hans: Han planlegger å stjele Koh-I-Noor, en diamant som dronning Victoria har. Siden Jacob vet at den kongelige gullsmeden drikker mye og ofte, bruker han sine egne "metoder" for å få tak i informasjonen han trenger.
98	Assassins Creed Syndicate del 70: Duleep Singh 8: The Great Jewel Heist	4	1	17:21	/ac_syndicate/ac_syndicate_del70_duleep_singh8.mp4	Duleep og snikmorderne finner ut hvor Koh-I-Noor er: I Tower of London. De kommer opp med en dobbelplan som gjør at Duleep og Jacob kan infiltrere Tower i løpet av en galla hvor man feirer det kongelige arsenal, samtidig som at Evie kan sikre utkantene. Jacobs mål er å få tak i diamanten og gi den til Evie, som så vil komme seg unna via hustakene.
99	Assassins Creed Syndicate del 71: Duleep Singh 9: The Sandman	4	1	15:49	/ac_syndicate/ac_syndicate_del71_duleep_singh9.mp4	Snikmorderne bestemmer seg for å finne ut av hvem det er som vil "stilne" Duleep Singh. Dette skjer under en trussel fra British Indies Company.
100	Assassins Creed Syndicate del 72: The Final Showdown	4	1	12:35	/ac_syndicate/ac_syndicate_del72_duleep_singh10.mp4	En forvirret, trist og rasende Duleep legger ut på en egen reise for å spore opp Brinley Ellsworth.
16	Rise of the Tomb Raider del 01	3	1	57:42	/rise_of_the_tomb_raider/Rise_of_the_Tomb_Raider_del1.mp4	Lara reiser til Syria på jakt etter en grav som skal inneholde den guddommelig kilde, men som heller viser seg å være tom. I tillegg møter hun på spillets fiende, Trinity. Lara innser at den gdudommelige kilde befinner seg i den skjulte byen Kitezh, i Sibir. 
101	Tomb Raider del 01	5	1	1:28:00	/tomb_raider_2013/tomb_raider_del01.mp4	Båten Lara er ombord i, synker og Lara må finne de andre overlevende. Lara må nedkjempe noen ulver, samtidig som hun møter på Mathias, en person som ikke er særlig vennlig…
102	Tomb Raider del 02	5	1	43:34	/tomb_raider_2013/tomb_raider_del02.mp4	Lara finner en hardt skadet Roth like ved et leirbål, og bestemmer seg for å hjelpe ham. Problemet er bare det at medisinpakken er i en hule som er full av ulver.
103	Tomb Raider del 03	5	1	1:39:25	/tomb_raider_2013/tomb_raider_del03.mp4	Lara sender et mayday for å gjøre folk på fastlandet oppmerksomme på at de har strandet på en øde øy. For å få sendt denne meldingen må hun for all del ikke ha noen som helst form for høydeskrekk.
104	Tomb Raider del 04	5	1	50:36	/tomb_raider_2013/tomb_raider_del04.mp4	Dette er en episode hvor det er mye utforskning og opplukking av dokumenter, gjenstander, etc i Mountain Village. I tillegg besøkes gravstedet Hall of Ascension.
107	Tomb Raider del 05	5	1	1:45:48	/tomb_raider_2013/tomb_raider_del05.mp4	Lara forlater Mountain Village og kommer til et slags gudshus hvor hun får sin første "samtale" med Himiko, og oppdager ritualet som Himiko bruker for å velge etterfølgeren sin. Etter en dramatisk tur ned fjellet kommer hun frem til Shantytown og får nok et dramatisk møte med fiendene.
108	Tomb Raider del 06	5	1	1:10:08	/tomb_raider_2013/tomb_raider_del06.mp4	Lara tar seg gjennom Shantytown og møter på Grimm. I løpet av episoden besøkes også de to gravstedene Well of Tears og Chamber of Judgement.
109	Tomb Raider del 07	5	1	2:05:56	/tomb_raider_2013/tomb_raider_del07.mp4	Lara forlater Shantytown, og etter en svært dramatisk tur gjennom noen katakomber, kommer hun til slutt fram til Summit Forest.
110	Tomb Raider del 08	5	1	1:39:05	/tomb_raider_2013/tomb_raider_del08.mp4	Lara utforsker Summit Forest, for så å ta turen tilbake til "katakomben" og plukke opp gjenglemte gjenstander der. Hun utforsker også gravstedet Stormguard Sanctum i Summit Forest. Til slutt kommer hun fram til Shipwreck Beach.
111	Tomb Raider del 09	5	1	1:57:46	/tomb_raider_2013/tomb_raider_del09.mp4	Lara sendes til det som er igjen av The Endurance for å hente Alex, en person som virkelig har havnet i Laras vennefelle, og som må ofre alt for å holde fiendene unna. Samtidig besøkes gravstedene The Flooded Vault og Temple of the Handmaidens.
112	Tomb Raider del 10	5	1	1:41:29	/tomb_raider_2013/tomb_raider_del10.mp4	Lara tar seg til en researchbase og oppdager nok en mindre hyggelig ting om Himiko. Hun klarer til slutt å overbevise Reyes og Jonah om å bli med henne til ritualstedet.
113	Tomb Raider del 11	5	1	1:24:57	/tomb_raider_2013/tomb_raider_del11.mp4	I den spennende finalen står det endelige slaget mellom Lara og "The Oni", før bare Mathias kan hindre Lara i redde Sam og stoppe Himiko. 
114	Assassins Creed Syndicate del 73: Playing Politics	4	1	10:39	/ac_syndicate/ac_syndicate_del73.mp4	Jacob jakter på statsminister Disraeli på Sinopean Club for å spore opp den mystiske personen "B" som planlegger å myrde Disraeli.
115	Assassins Creed Syndicate del 74: The Bodyguard	4	1	7:25	/ac_syndicate/ac_syndicate_del74.mp4	Jacob tenker å advare Disraeli om drapstruslene mot ham og spør ham om hvem mannen i uniformen "B" er.
116	Assassins Creed Syndicate del 75: Driving Mrs. Disraeli	4	1	20:45	/ac_syndicate/ac_syndicate_del75.mp4	Mary-Anne Disraeli vil gjerne se Devils Acre og ber om hjelp fra sin nye livvakt Jacob.
117	Assassins Creed Syndicate del 76: Unbreaking the Bank	4	1	13:52	/ac_syndicate/ac_syndicate_del76.mp4	Etter at Jacob myrdet Twopenny besøker Evie sentrum i London.
118	Assassins Creed Syndicate del 77: Motion to Impeach	4	1	26:04	/ac_syndicate/ac_syndicate_del77.mp4	Jacob planlegger å drepe Jarlen av Cardigan innenfor det britiske parlamentets vegger.
119	Assassins Creed Syndicate del 78: Strange Bedfellows	4	1	16:43	/ac_syndicate/ac_syndicate_del78.mp4	Jacob godtar Maxwell Roths invitasjon til et møte.
120	Assassins Creed Syndicate del 79: Triple Theft	4	1	21:00	/ac_syndicate/ac_syndicate_del79.mp4	Jacob og Roth strever med å fange 3 av Strarricks medarbeidere i et forsøk på å ta kontroll over bydelen.
121	Assassins Creed Syndicate del 80: Fun And Games	4	1	14:20	/ac_syndicate/ac_syndicate_del80.mp4	Jacob og Roth planlegger å spre kaos ved å sprenge en av Starricks fabrikker.
122	Assassins Creed Syndicate del 81: Final Act	4	1	20:17	/ac_syndicate/ac_syndicate_del81.mp4	Jacob myrder Roth i Alhambra
123	Assassins Creed Syndicate del 82: Double Trouble	4	1	14:27	/ac_syndicate/ac_syndicate_del82.mp4	Jacob skaffer tilgang til et ball til seg selv og til Evie.
124	Assassins Creed Syndicate del 83: Dress to Impress	4	1	20:33	/ac_syndicate/ac_syndicate_del83.mp4	Jacob møter Abberline for å diskutere det å få med våpen inn i ballet.
125	Assassins Creed Syndicate del 84: Family Politics	4	1	15:03	/ac_syndicate/ac_syndicate_del84.mp4	Evie besøker Duleep Singh for å finne ut om det finnes en ekstra utgave av Buckingham-planene.
126	Assassins Creed Syndicate del 85: A Night to Remember (FINALE)	4	1	43:46	/ac_syndicate/ac_syndicate_del85.mp4	I det siste oppdraget i hovedhistorien må Jacob og Evie hindre Crawfor Starrick i å angripe ballet, for så å myrde ham og deretter ta kontroll over Eden-stykket (the Piece of Eden)
127	Assassins Creed Syndicate del 86: Queen Victoria 1: Operation: Dynamite Boat	4	1	08:49	/ac_syndicate/ac_syndicate_del86_queen_victoria1.mp4	En tempelridderfraksjon må hindres i å ta med dynamitt inn i London.
128	Assassins Creed Syndicate del 87: Queen Victoria 2: Operation Locomotive	4	1	06:21	/ac_syndicate/ac_syndicate_del87_queen_victoria2.mp4	Evie hindrer tempelridderne i å sende et tog som er fullastet med dynamitt til en stasjon som er full av mennesker.
129	Assassins Creed Syndicate del 88: Queen Victoria 3: Operation: Drive for Lives	4	1	05:46	/ac_syndicate/ac_syndicate_del88_queen_victoria3.mp4	Evie sporer opp enn unnsluppet leder av de nyoppstartede tempelridderne.
130	Assassins Creed del 89: Queen Victoria 4: Operation Westminster (SISTE EPISODE)	4	1	13:59	/ac_syndicate/ac_syndicate_del89_queen_victoria4.mp4	Evie stopper tempelridderne fra å sprenge Parlamentet (Hose of Parliament)
\.


--
-- Name: film_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('film_id_seq', 130, true);


--
-- Data for Name: filmtype; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY filmtype (typenr, typenavn) FROM stdin;
0	Ingen type
1	Let's play
2	Feriefilmer
\.


--
-- Data for Name: serie; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY serie (serienr, serienavn, typenr, seriebeskrivelse) FROM stdin;
0	Ingen serie	0	\N
2	Ferietur 2015	2	\N
1	Quantum Break	1	Quantum Break er et spill hvor hovedkarakteren forsøker å stoppe tiden i å kollapse, for på den måten å hindre verdens undergang
4	Assassins Creed Syndicate	1	I dette spillet følger man for første gang (i denne spillserien) en kvinnelig karakter. Søskenparet Evie og Jacob Frye er i London for å kjempe mot The Blighters og erkefienden, tempelridderne
3	Rise of the Tomb Raider	1	I Rise of the Tomb Raider er Lara Croft på jakt etter "den guddommelige kilde" i et spill som tar oss fra Syria til Sibir. Problemet hennes er at hun ikke er alene om å jakte på denne kilden.
5	Tomb Raider (2013)	1	I dette spillet følger vi en ung utgave av Lara Croft når hun og vennene hennes strander på ei øy sør for Japan, på jakt etter stedet Yamatai. På øya møter hun på mange fiender som har overlevd ved å myrde andre, og på Himiko, ei rasende dronning som forårsaker en hel del uvær rundt øya. Klarer Lara å nedkjempe Himiko og de andre fiendene?
\.


--
-- Name: film film_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY film
    ADD CONSTRAINT film_pkey PRIMARY KEY (filmnr);


--
-- Name: serie serie_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY serie
    ADD CONSTRAINT serie_pkey PRIMARY KEY (serienr);


--
-- Name: filmtype type_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY filmtype
    ADD CONSTRAINT type_pkey PRIMARY KEY (typenr);


--
-- Name: film film_serienr_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY film
    ADD CONSTRAINT film_serienr_fkey FOREIGN KEY (serienr) REFERENCES serie(serienr);


--
-- Name: film film_typenr_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY film
    ADD CONSTRAINT film_typenr_fkey FOREIGN KEY (typenr) REFERENCES filmtype(typenr);


--
-- Name: serie serie_typenr_fkey; Type: FK CONSTRAINT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY serie
    ADD CONSTRAINT serie_typenr_fkey FOREIGN KEY (typenr) REFERENCES filmtype(typenr);


--
-- PostgreSQL database dump complete
--


/*
 * Copyright (c) 2017, Anders Bolt-Evensen
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Anders Bolt-Evensen BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


using System;
using System.Collections.Generic;
using System.Text;
using Npgsql;
using System.Threading;
using System.Data;
using System.Net.Sockets;
using System.IO;
using System.Collections;

namespace JobbWPF
{
    class pgsql
    {
        private NpgsqlConnection conn;
        private NpgsqlCommand cmd;
        private NpgsqlDataReader reader;
        private String username, password;
        private List<string> data;
        private string server, database = "jobber";
        private int record;
        //public string[] colNames;
        private string title;
        public pgsql(string newTitle)
        {
            title = newTitle;
        }

        /// <summary>
        /// Initializes the database
        /// </summary>
        public bool Init()
        {
            try
            {
                conn = new NpgsqlConnection("Host=" + server + ";Username=" + username + ";Password=" + password + ";Database=" + database);
                conn.Open();
                cmd = new NpgsqlCommand();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                throw ne; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs
            }
            catch (SocketException se)
            {
                setError(se.Message);
                throw se; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs, med mindre den eksterne serveren kobles fra.
            }
            catch(TimeoutException te)
            {
                throw te;
            }
            catch (Exception e)
            {
                setError(e.Message);
                throw e; // Kaster unntaket videre. Normalt sett vil dette kun påvirke koden i connectPgsql.cs, med mindre den eksterne serveren kobles fra.
            }
        }

        // Metoder som sjekker om tabellene finnes i databasen.
        // Det skal være fire tabeller: Søknad, sted, land og status
        // i tillegg til ett "view" som kobler sammen de fire tabellene

        /// <summary>
        /// Checks if the table "steder" (towns) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool tableTownExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT stedid FROM sted WHERE stedid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch(NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Checks if the table "søknader" (applications) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool tableApplicationExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT soknadid FROM soknad WHERE soknadid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Checks if the table "land" (countries) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool tableCountryExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT landid FROM land WHERE landid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Checks if the table "statuser" (statuses) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool tableStatusExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT statusid FROM status WHERE statusid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Checks if the view "view_soknad" (søknad = application) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool viewApplicationExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT soknadid FROM view_soknad WHERE soknadid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Checks if the view "view_sted" (sted = town, city, place) exists in the database by attempting to select the first item in the database
        /// </summary>
        /// <returns>True on success (the table exists and is accessible) and false otherwise.</returns>
        public bool viewTownExists()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT stedid FROM view_sted WHERE stedid=1";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException)
            {
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        // Slutt på metoder som sjekker om tabellene finnes i databasen.
        // Metoder som oppretter tomme tabeller:

        public bool createTableTowns()
        {
            try
            {
                createSequenceStedidSeq();
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TABLE public.sted(stedid integer NOT NULL DEFAULT nextval('stedid_seq'::regclass), stedsnavn text COLLATE pg_catalog.\"default\" NOT NULL, landid integer NOT NULL, CONSTRAINT sted_pkey PRIMARY KEY(stedid), CONSTRAINT unikt_sted UNIQUE(stedsnavn), CONSTRAINT sted_landid_fkey FOREIGN KEY(landid) REFERENCES public.land(landid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION) WITH(OIDS = FALSE) TABLESPACE pg_default;";
                reader = cmd.ExecuteReader();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createTableApplications()
        {
            try
            {
                createSequenceSoknadidSeq();
                createFunctionEmpty();
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TABLE public.soknad(soknadid integer NOT NULL DEFAULT nextval('soknadid_seq'::regclass), tittel text COLLATE pg_catalog.\"default\" NOT NULL, bedrift text COLLATE pg_catalog.\"default\" NOT NULL, stedid integer NOT NULL, statusid integer NOT NULL, soknadsfrist text COLLATE pg_catalog.\"default\" NOT NULL, motivasjon text COLLATE pg_catalog.\"default\", CONSTRAINT soknad_pkey PRIMARY KEY(soknadid), CONSTRAINT unik_soknad UNIQUE(tittel, bedrift, stedid), CONSTRAINT soknad_statusid_fkey FOREIGN KEY(statusid) REFERENCES public.status(statusid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION, CONSTRAINT soknad_stedid_fkey FOREIGN KEY(stedid) REFERENCES public.sted(stedid) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION, CONSTRAINT chk CHECK(NOT empty(tittel)), CONSTRAINT chkbedriftnotempty CHECK(NOT empty(bedrift)), CONSTRAINT chksoknadsfristnotempty CHECK(NOT empty(soknadsfrist)))WITH(OIDS = FALSE)TABLESPACE pg_default;";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch(NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createTableCountries()
        {
            try
            {
                createSequenceLandidSeq();
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TABLE public.land(landid integer NOT NULL DEFAULT nextval('landid_seq'::regclass), land text COLLATE pg_catalog.\"default\" NOT NULL, CONSTRAINT land_pkey PRIMARY KEY(landid), CONSTRAINT unikt_land UNIQUE(land))WITH(OIDS = FALSE)TABLESPACE pg_default; ";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createTableStatuses()
        {
            try
            {
                createSequenceStatusidSeq();
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TABLE public.status(statusid integer NOT NULL DEFAULT nextval('statusid_seq'::regclass), status character varying(30) COLLATE pg_catalog.\"default\" NOT NULL, CONSTRAINT status_pkey PRIMARY KEY(statusid), CONSTRAINT unik_status UNIQUE(status))WITH(OIDS = FALSE)TABLESPACE pg_default;";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError(e.Message);
                return false;
            }

            finally
            {
                conn.Close();
            }
        }

        public bool createViewApplications()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE OR REPLACE VIEW public.view_soknad AS SELECT soknad.soknadid, soknad.tittel, soknad.bedrift, soknad.soknadsfrist, soknad.stedid, sted.stedsnavn, sted.landid, land.land, soknad.statusid, status.status, soknad.motivasjon FROM soknad JOIN sted ON sted.stedid = soknad.stedid JOIN land ON land.landid = sted.landid JOIN status ON status.statusid = soknad.statusid ORDER BY soknad.soknadid;";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createViewTown()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE OR REPLACE VIEW public.view_sted AS SELECT sted.stedid, sted.stedsnavn, sted.landid, land.land FROM sted JOIN land ON land.landid = sted.landid;";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        // Slutt på funksjoner som oppretter tabeller og views.
        // Metoder som oppretter sekvenser som brukes til å automatisk øke ID med 1.
        private void createSequenceLandidSeq()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE SEQUENCE landid_seq;";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlException)
            {
                return;
            }
            finally
            {
                conn.Close();
            }
        }
        private void createSequenceStedidSeq()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE SEQUENCE stedid_seq;";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlException)
            {
                return;
            }
            finally
            {
                conn.Close();
            }
        }
        private void createSequenceSoknadidSeq()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE SEQUENCE soknadid_seq;";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlException)
            {
                return;
            }
            finally
            {
                conn.Close();
            }
        }
        private void createSequenceStatusidSeq()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE SEQUENCE statusid_seq;";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlException)
            {
                return;
            }
            finally
            {
                conn.Close();
            }
        }

        // Metoder som oppretter lagrede prosedyrer og triggere.
        // Disse metodene kjøres som del av metodene over og er derfor private.
        public bool createFunctionEmpty()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE OR REPLACE FUNCTION public.empty(text) RETURNS boolean LANGUAGE 'sql' COST 100 IMMUTABLE AS $BODY$ SELECT $1 ~'^[[:space:]]*$'; $BODY$; COMMENT ON FUNCTION public.empty(text) IS 'Sjekke innholdet i en streng. Returnerer sann om strengen er tom eller bare inneholder mellomrom, og falsk ellers.';";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                throw ne;
            }
            finally
            {
                conn.Close();
            }
        }
        public bool createProcedureNewCountryID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE FUNCTION public.nylandid() RETURNS trigger LANGUAGE 'plpgsql' COST 100 VOLATILE NOT LEAKPROOF AS $BODY$ BEGIN RAISE NOTICE 'Landet % med ID % ble lagt inn i databasen.', NEW.land, NEW.landid; RETURN NEW; END; $BODY$; ";
                cmd.ExecuteNonQuery();
                return createTriggerNewCountryID();
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createProcedureNewApplicationID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE FUNCTION nysoknadid() RETURNS trigger LANGUAGE plpgsql AS $$ BEGIN RAISE NOTICE 'Søknad med ID % ble lagt inn i databasen.', NEW.soknadid; RETURN NEW; END; $$; ";
                cmd.ExecuteNonQuery();
                return createTriggerNewApplicationID();
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createProcedureNewTownID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE FUNCTION nystedid() RETURNS trigger LANGUAGE plpgsql AS $$ BEGIN RAISE NOTICE 'Sted % med ID % ble lagt inn i databasen.', NEW.stedsnavn, NEW.stedid; RETURN NEW; END; $$";
                cmd.ExecuteNonQuery();
                return createTriggerNewTownID();
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        public bool createProcedureUpdateApplication()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                //cmd.CommandText = "CREATE FUNCTION updatesoknad() RETURNS trigger LANGUAGE plpgsql AS $$DECLARE counter_ integer:= 0; tablename_ text := 'temptable'; oldStatus text; newStatus text; max int; updated boolean := false; BEGIN begin --raise notice 'Creating table %', tablename_; execute 'create temporary table ' || tablename_ || ' (counter integer) on commit drop'; execute 'insert into ' || tablename_ || ' (counter) values(0)'; execute 'select counter from ' || tablename_ into counter_; --raise notice 'Actual value for counter= [%]', counter_; exception when duplicate_table then null; end; execute 'select counter from ' || tablename_ into counter_; execute 'update ' || tablename_ || ' set counter = counter + 1'; --raise notice 'updating'; execute 'select counter from ' || tablename_ into counter_; --raise notice 'Actual value for counter= [%]', counter_; max:= count(soknadid) from soknad; if counter_ = max then raise exception 'Kan ikke oppdatere mer enn Ã©n rad om gangen.'; end if; if NEW.soknadid != OLD.soknadid then raise notice 'Søknadid-en ble endret fra % til %.', OLD.soknadid, NEW.soknadid; updated = true; end if; if NEW.tittel != OLD.tittel then raise notice 'Søknaden med ID % har fÃ¥tt endret tittel fra % til %.', OLD.soknadid, OLD.tittel, NEW.tittel; updated = true; end if; if NEW.bedrift != OLD.bedrift then raise notice 'Søknaden med ID % har fÃ¥tt endret bedrift fra % til %.', OLD.soknadid, OLD.bedrift, NEW.bedrift; updated = true; end if; if NEW.stedid != OLD.stedid then raise notice 'Søknaden med ID % har fÃ¥tt endret stedid fra % til %.', OLD.soknadid, OLD.stedid, NEW.stedid; updated = true; end if; if NEW.soknadsfrist != OLD.soknadsfrist then raise notice 'Søknaden med ID % har fÃ¥tt endret søknadsfrist fra % til %.', OLD.soknadid, OLD.soknadsfrist, NEW.soknadsfrist; updated = true; end if; if NEW.motivasjon != OLD.motivasjon then raise notice 'Søknaden med ID % har fÃ¥tt endret motivasjon fra % til %.', OLD.soknadid, OLD.motivasjon, NEW.motivasjon; updated = true; end if; if NEW.statusid != OLD.statusid then if OLD.statusid = 1 then oldStatus = 'Registrert'; elsif OLD.statusid = 2 then oldStatus = 'Sendt'; elsif OLD.statusid = 3 then oldStatus = 'Interessert, mulig intervju'; elsif OLD.statusid = 4 then oldStatus = 'Avvist'; elsif OLD.statusid = 5 then oldStatus = 'Søknad skrevet, men ikke sendt'; elsif OLD.statusid = 6 then oldStatus = 'Godtatt, klar for jobb'; end if; if NEW.statusid = 1 then newStatus = 'Registrert'; elsif NEW.statusid = 2 then newStatus = 'Sendt'; elsif NEW.statusid = 3 then newStatus = 'Interessert, mulig intervju'; elsif NEW.statusid = 4 then newStatus = 'Avvist'; elsif NEW.statusid = 5 then newStatus = 'Søknad skrevet, men ikke sendt'; elsif NEW.statusid = 6 then newStatus = 'Godtatt, klar for jobb'; end if; raise notice 'Søknaden med ID % har fÃ¥tt endret statusid fra % (%) til % (%).', OLD.soknadid, OLD.statusid, oldStatus, NEW.statusid, newStatus; elsif NEW.statusid = OLD.statusid then if updated = false then if OLD.statusid = 1 then oldStatus = 'Registrert'; elsif OLD.statusid = 2 then oldStatus = 'Sendt'; elsif OLD.statusid = 3 then oldStatus = 'Interessert, mulig intervju'; elsif OLD.statusid = 4 then oldStatus = 'Avvist'; elsif OLD.statusid = 5 then oldStatus = 'Søknad skrevet, men ikke sendt'; elsif OLD.statusid = 6 then oldStatus = 'Godtatt, klar for jobb'; end if; raise notice 'Søknaden med ID % har IKKE fått endret status. Statusen forblir % (%).', OLD.soknadid, OLD.statusid, oldStatus; end if; end if; RETURN NEW; END; $$;";
                cmd.CommandText = "CREATE FUNCTION updatesoknad() RETURNS trigger \n" +
                "LANGUAGE plpgsql \n"+
                "AS $$DECLARE \n"+
            "counter_ integer := 0; \n"+
            "tablename_ text := 'temptable'; \n"+
            "oldStatus text; \n"+
            "newStatus text; \n"+
            "max int; \n"+
            "updated boolean := false; \n"+
            "BEGIN \n"+
            "begin \n"+
            "        --raise notice 'Creating table %', tablename_; \n"+
            "        execute 'create temporary table ' || tablename_ || ' (counter integer) on commit drop'; \n"+
            "        execute 'insert into ' || tablename_ || ' (counter) values(0)'; \n"+
            "        execute 'select counter from ' || tablename_ into counter_; \n"+
            "        --raise notice 'Actual value for counter= [%]', counter_; \n"+
            "    exception \n"+
            "        when duplicate_table then \n"+
            "        null; \n"+
            "    end; \n"+
            "execute 'select counter from ' || tablename_ into counter_; \n"+
            "    execute 'update ' || tablename_ || ' set counter = counter + 1'; \n"+
            "   --raise notice 'updating'; \n"+
            "    execute 'select counter from ' || tablename_ into counter_; \n"+
            "    --raise notice 'Actual value for counter= [%]', counter_; \n"+
            "    max := count(soknadid) from soknad; \n"+
            "    if counter_ = max then \n"+
            "        raise exception 'Kan ikke oppdatere mer enn én rad om gangen.'; \n"+
            "    end if; \n"+
            "if NEW.soknadid != OLD.soknadid \n"+
            "then \n"+
            "raise notice 'Søknadid-en ble endret fra % til %.', OLD.soknadid, NEW.soknadid; \n"+
            "updated = true; \n"+
            "end if; \n"+
            "if NEW.tittel != OLD.tittel \n"+
            "then \n"+
            "raise notice 'Søknaden med ID % har fått endret tittel fra % til %.', OLD.soknadid, OLD.tittel, NEW.tittel; \n"+
            "updated=true; \n"+
            "end if; \n"+
            "if NEW.bedrift != OLD.bedrift \n"+
            "then \n"+
            "raise notice 'Søknaden med ID % har fått endret bedrift fra % til %.', OLD.soknadid, OLD.bedrift, NEW.bedrift; \n"+
            "updated=true; \n"+
            "end if; \n"+
            "if NEW.stedid != OLD.stedid \n"+
            "then \n"+
            "raise notice 'Søknaden med ID % har fått endret stedid fra % til %.', OLD.soknadid, OLD.stedid, NEW.stedid; \n"+
            "updated=true; \n"+
            "end if; \n"+
            "if NEW.soknadsfrist != OLD.soknadsfrist \n"+
            "then \n"+
            "raise notice 'Søknaden med ID % har fått endret søknadsfrist fra % til %.', OLD.soknadid, OLD.soknadsfrist, NEW.soknadsfrist; \n"+
            "updated = true; \n"+
            "end if; \n"+
            "if NEW.motivasjon != OLD.motivasjon \n"+
            "then \n"+
            "raise notice 'Søknaden med ID % har fått endret motivasjon fra % til %.', OLD.soknadid, OLD.motivasjon, NEW.motivasjon; \n"+
            "updated = true; \n"+
            "end if; \n"+
            "if NEW.statusid != OLD.statusid \n"+
            "then \n"+
            "if OLD.statusid = 1 \n"+
            "then \n"+
            "oldStatus = 'Registrert'; \n"+
            "elsif OLD.statusid = 2 \n"+
            "then \n"+
            "oldStatus = 'Sendt'; \n"+
            "elsif OLD.statusid = 3 \n"+
            "then \n"+
            "oldStatus = 'Interessert, mulig intervju'; \n"+
            "elsif OLD.statusid = 4 \n"+
            "then \n"+
            "oldStatus = 'Avvist'; \n"+
            "elsif OLD.statusid = 5 \n"+
            "then \n"+
            "oldStatus = 'Søknad skrevet, men ikke sendt'; \n"+
            "elsif OLD.statusid = 6 \n"+
            "then \n"+
            "oldStatus = 'Avvist etter intervju'; \n"+
            "elsif OLD.statusid = 7 \n"+
            "then \n"+
            "oldStatus = 'Godtatt, klar for jobb'; \n"+
            "end if; \n"+
            "if NEW.statusid = 1 \n"+
            "then \n"+
            "newStatus = 'Registrert'; \n"+
            "elsif NEW.statusid = 2 \n"+
            "then \n"+
            "newStatus = 'Sendt'; \n"+
            "elsif NEW.statusid = 3 \n"+
            "then \n"+
            "newStatus = 'Interessert, mulig intervju'; \n"+
            "elsif NEW.statusid = 4 \n"+
            "then \n"+
            "newStatus = 'Avvist'; \n"+
            "elsif NEW.statusid = 5 \n"+
            "then \n"+
            "newStatus = 'Søknad skrevet, men ikke sendt'; \n"+
            "elsif NEW.statusid = 6 \n"+
            "then \n"+
            "newStatus = 'Avvist etter intervju'; \n"+
            "elsif NEW.statusid = 7 \n"+
            "then \n"+
            "newStatus = 'Godtatt, klar for jobb'; \n"+
            "end if; \n"+
            "raise notice 'Søknaden med ID % har fått endret statusid fra % (%) til % (%).', OLD.soknadid, OLD.statusid, oldStatus, NEW.statusid, newStatus; \n"+
            "elsif NEW.statusid = OLD.statusid \n"+
            "then \n"+
            "if updated = false \n"+
            "then \n"+
            "if OLD.statusid = 1 \n"+
            "then \n"+
            "oldStatus = 'Registrert'; \n"+
            "elsif OLD.statusid = 2 \n"+
            "then \n"+
            "oldStatus = 'Sendt'; \n"+
            "elsif OLD.statusid = 3 \n"+
            "then \n"+
            "oldStatus = 'Interessert, mulig intervju'; \n"+
            "elsif OLD.statusid = 4 \n"+
            "then \n"+
            "oldStatus = 'Avvist'; \n"+
            "elsif OLD.statusid = 5 \n"+
            "then \n"+
            "oldStatus = 'Søknad skrevet, men ikke sendt'; \n"+
            "elsif OLD.statusid = 6 \n"+
            "then \n"+
            "oldStatus = 'Avvist etter intervju'; \n"+
            "elsif OLD.statusid = 7 \n"+
            "then \n"+
            "oldStatus = 'Godtatt, klar for jobb'; \n"+
            "end if; \n"+
            "raise notice 'Søknaden med ID % har IKKE fått endret status. Statusen forblir % (%).', OLD.soknadid, OLD.statusid, oldStatus; \n"+
            "end if; \n"+
            "end if; \n"+
            "RETURN NEW; \n"+
            "END; \n"+
            "$$;";
                cmd.ExecuteNonQuery();
                return createTriggerUpdateApplication();
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        private bool createTriggerNewCountryID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TRIGGER trg_nyttland AFTER INSERT ON public.land FOR EACH ROW EXECUTE PROCEDURE public.nylandid();";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        private bool createTriggerNewApplicationID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TRIGGER trg_nysoknad AFTER INSERT ON public.soknad FOR EACH ROW EXECUTE PROCEDURE public.nysoknadid();";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        private bool createTriggerNewTownID()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TRIGGER trg_nyttsted AFTER INSERT ON public.sted FOR EACH ROW EXECUTE PROCEDURE public.nystedid();";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        private bool createTriggerUpdateApplication()
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "CREATE TRIGGER trg_oppdatersoknad AFTER UPDATE ON public.soknad FOR EACH ROW EXECUTE PROCEDURE public.updatesoknad();";
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        // Slutt på metoder som oprretter triggere.

        public void setRecord(int newRecord)
        {
            record = newRecord;
        }
        public int getRecord()
        {
            return record;
        }
        string errMsg;
        public string getError()
        {
            return errMsg;
        }
        public void setError(string newErrMsg)
        {
            errMsg = newErrMsg;
        }

        public string[] GetTitle(string sqlQuery)
        {
            string[] res = null;
            Init();
            cmd = new NpgsqlCommand(sqlQuery);
            cmd.Connection = conn;
            NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
            DataTable dt = new DataTable();
            int rows = nad.Fill(dt);
            if (sqlQuery.ToLower().StartsWith("select"))
            {
                reader = cmd.ExecuteReader();
                int j = 0;
                while (reader.Read())
                {
    int i = 0;
    res = new string[reader.FieldCount];
    while (i < reader.FieldCount)
    {
        if (j == 0)
        {
            if (i == reader.FieldCount - 1)
            {
                res[i] = reader.GetName(i) + "\n";
                j++;
            }
            else
            {
                res[i] = reader.GetName(i) + "\t";
            }

        }
        i++;
    }
    return res;
                }
            }
            return res;
        }

        public string[] Exec(string sqlQuery)
        {
            StringBuilder sb = new StringBuilder();
            string[] res = null;
            Init();
            cmd = new NpgsqlCommand(sqlQuery);
            cmd.Connection = conn;
            NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
            DataTable dt = new DataTable();
            int rows = nad.Fill(dt);
            if (sqlQuery.ToLower().StartsWith("select"))
            {
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
    res = new string[rows];
    int i = 0, j = 0;
    while (i < reader.FieldCount)
    {
        if (j == 0)
        {
            if (i == reader.FieldCount - 1)
            {
                sb.Append(reader.GetName(i) + "\n");
                j++;
            }
            else
            {
                sb.Append(reader.GetName(i) + "\t");
            }
        }
        i++;
    }
    i = 0;
    while (i < reader.FieldCount)
    {

        if (i == reader.FieldCount - 1)
        {
            res[i] = reader.GetString(i) + "\n";
        }
        else
        {
            res[i] = reader.GetString(i) + "\t";
        }
        i++;
    }
    return res;
                }
            }
            return res;
        }

        /// <summary>
        /// Executes an SQL query. This is only intended to be run from SQLCommands.cs.
        /// </summary>
        /// <param name="sqlQuery">The query to be executed.</param>
        /// <returns></returns>
        public string ExecQry(string sqlQuery)
        {
            try
            {
                string res = "";
                StringBuilder sb = new StringBuilder();
                Init();
                cmd = new NpgsqlCommand(sqlQuery);
                cmd.Connection = conn;
                NpgsqlDataAdapter nad = new NpgsqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                int rows = nad.Fill(dt);
                if (sqlQuery.StartsWith("select"))
                {
    int j = 0;
    reader = cmd.ExecuteReader();
    while (reader.Read())
    {
        int i = 0;
        while (i < reader.FieldCount)
        {
            if (j == 0)
            {
                if (i == reader.FieldCount - 1)
                {
    sb.AppendLine(reader.GetName(i) + "\n");
    j++;
                }
                else
                {
    sb.Append(reader.GetName(i) + " \t | ");
                }
            }
            i++;
        }
        i = 0;
        while (i < reader.FieldCount)
        {

            if (i == reader.FieldCount - 1)
                sb.AppendLine(reader.GetString(i) + "\n");
            else
                sb.Append(reader.GetString(i) + " \t | ");
            i++;
        }
    }
    res = sb.ToString() + "\n(" + rows.ToString() + " rader)";
                }
                else if (sqlQuery.StartsWith("explain"))
                {
    int j = 0;
    reader = cmd.ExecuteReader();
    while (reader.Read())
    {
        int i = 0;
        while (i < reader.FieldCount)
        {
            if (j == 0)
            {
                if (i == reader.FieldCount - 1)
                {
    sb.AppendLine(reader.GetName(i) + "\n");
    j++;
                }
                else
                {
    sb.Append(reader.GetName(i) + "\t");
                }
            }
            i++;
        }
        i = 0;
        while (i < reader.FieldCount)
        {

            if (i == reader.FieldCount - 1)
                sb.AppendLine(reader.GetString(i) + "\n");
            else
                sb.Append(reader.GetString(i) + "\t");
            i++;
        }
    }
    res = sb.ToString() + "\n(" + rows.ToString() + " rader)";
                }
                else
                {
    sb.AppendLine(cmd.ExecuteNonQuery() + " rader ble endret.");
                }
                res = sb.ToString();
                return res;
            }
            catch (NpgsqlException npe)
            {
                return npe.Message;
            }

            finally
            {
                conn.Close();
            }
        }


        /// <summary>
        /// Returns the username.
        /// </summary>
        /// <returns>The PostgreSQL username</returns>
        public String GetUsername()
        {
            return username;
        }
        /// <summary>
        /// Returns the PostgreSQL password
        /// </summary>
        /// <returns>The PostgreSQL password</returns>
        public String GetPassword()
        {
            return password;
        }
        /// <summary>
        /// Sets the password to be used when attempting to connect to the PostgreSQL server.
        /// </summary>
        /// <param name="newPassword"></param>
        public void SetPassword(String newPassword)
        {
            password = newPassword;
        }

        /// <summary>
        /// Sets the username to be used when attempting to connect to the PostgreSQL server.
        /// </summary>
        /// <param name="newUsername"></param>
        public void SetUsername(String newUsername)
        {
            username = newUsername;
        }
        public void SetServer(string newServer)
        {
            server = newServer;
        }

        /// <summary>
        /// Inserts a new status to the database.
        /// </summary>
        /// <param name="status">The new status</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertStatus(string status)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO status (status) VALUES('" + status + "');", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn den nye statusen. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye statusen. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye statusen. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Inserts a new town to the database
        /// </summary>
        /// <param name="townName">The name of the town</param>
        /// <param name="countryID">The ID of the country where the town is located</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertTown(string townName, int countryID)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO sted (stedsnavn, landid) VALUES('" + townName + "', " + countryID + ");", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch(SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch(TimeoutException te)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye byen/stedet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Setter inn et nytt navn i databasen.
        /// </summary>
        /// <param name="countryName">Navnet på det nye landet. Må være unikt.</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertCountry(string countryName)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand("INSERT INTO land (land) VALUES('" + countryName + "');", conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn det nye landet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn det nye landet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn det nye landet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Inserts a new job "application" into the database.
        /// </summary>
        /// <param name="title">The title of the job</param>
        /// <param name="company">The company that offers the job</param>
        /// <param name="placeID">int: The ID of the city where the job is located.</param>
        /// <param name="countryID">int: The ID of the country where the job is located.</param>
        /// <param name="statusID">int: The status of the job application</param>
        /// <param name="date">The deadline for when the application has to be sent.</param>
        /// <returns>True if the insert succeeds and false if it fails</returns>
        public bool InsertApplication(string title, string company, int townID, int statusID, string date, string motivation)
        {
            Init();
            try
            {
                cmd = new NpgsqlCommand("INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon) VALUES('" + title + "', '" + company + "'," + townID + ", " + statusID + ", '" + date + "','" + motivation + "');", conn);
                cmd.ExecuteNonQuery();

                return true;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke sette inn den nye søknaden. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke sette inn den nye søknaden. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke sette inn den nye søknaden. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Counts the total number of applications.
        /// </summary>
        /// <returns>The total number of applications.</returns>
        public double countTotalApplications()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of applications that the employer have not responded to.
        /// </summary>
        /// <returns>Number of unanswered applications</returns>
        public double countUnansweredApplications()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=2";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts applications that have been added to the database, but not yet sent or written.
        /// </summary>
        /// <returns>Number of unsent, unwritten applications</returns>
        public double countRegisteredNotSentApplications()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=1";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of applications that have been declined after an interview.
        /// </summary>
        /// <returns>Number of applications that have been declined after an interview</returns>
        public double countDeclinedAfterInterview()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=6";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of applications that have been declined by the employer.
        /// </summary>
        /// <returns>Number of declined jobs</returns>
        public double countDeclinedApplications()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=4";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of applications that the employer finds interesting and have lead to an interview
        /// </summary>
        /// <returns>The number of application that have lead to a job interview.</returns>
        public double countAcceptedForInterview()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=3";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of applications that the employer accepted which then have lead to a job.
        /// </summary>
        /// <returns>Number of accepted applications</returns>
        public double countAcceptedForWork()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=7";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Counts the number of written applications that is yet to be sent.
        /// </summary>
        /// <returns>Number of written, unsent applications</returns>
        public double countWrittenButNotSent()
        {
            int res = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad WHERE statusid=5";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res++;
            return res;
        }

        /// <summary>
        /// Builds a list of strings containing all data about a given job application.
        /// </summary>
        /// <param name="index">The application ID</param>
        /// <returns>A list of string that contains all information about the current job.</returns>
        public List<string> GetApplications(int index)
        {
            Init();
            cmd = new NpgsqlCommand();
            List<string> data = new List<string>();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT tittel, bedrift, stedid, stedsnavn, landid, land, statusid, status, soknadsfrist, motivasjon FROM view_soknad WHERE soknadid = " + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0)); // Title
                data.Add(reader.GetString(1)); // Bedrift
                data.Add(reader.GetString(2)); // Stedid
                data.Add(reader.GetString(3)); // Sted (by)
                data.Add(reader.GetString(4)); // LandID
                data.Add(reader.GetString(5)); // Land
                data.Add(reader.GetString(6)); // StatusID
                data.Add(reader.GetString(7)); // Status
                data.Add(reader.GetString(8)); // Soknadsfrist
                if (!reader.IsDBNull(9))
                    data.Add(reader.GetString(9)); // Motivasjon
                else
                    data.Add("");
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Fetches the company name based on the application ID.
        /// </summary>
        /// <param name="appID">The ID of the application in question.</param>
        /// <returns>A string with the company name.</returns>
        public string getCompany(int appID)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT bedrift FROM soknad WHERE soknadid = " + appID + "ORDER BY statusid asc";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            return res;
        }

        /// <summary>
        /// Builds a list of statuses based on the status ID.
        /// </summary>
        /// <param name="index">The Status ID.</param>
        /// <returns>A list of strings with all information about the status.</returns>
        public List<string> GetStatuses(int index)
        {
            Init();
            List<string> data = new List<string>();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT * FROM status WHERE statusid = " + index + "ORDER BY statusid asc";
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0));
                data.Add(reader.GetString(1));
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Builds a list with all data about a city based of the ID.
        /// </summary>
        /// <param name="index">The city/town ID.</param>
        /// <returns>A list with all information about the city.</returns>
        public List<string> GetCities(string name)
        {
            try
            {
                Init();
                List<string> data = new List<string>();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT * FROM view_sted WHERE stedsnavn = '" + name + "'";
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
    data.Add(reader.GetString(0));
    data.Add(reader.GetString(1));
    data.Add(reader.GetString(2));
    data.Add(reader.GetString(3));
                }
                conn.Close();
                return data;
            }
            catch(NpgsqlException ne)
            {
                setError(ne.Message);
                throw ne;
            }
            catch(Exception e)
            {
                setError(e.ToString());
                throw e;
            }
        }

        /// <summary>
        /// Builds a list with all information about the country based on its ID.
        /// </summary>
        /// <param name="index">The ID of the country in question</param>
        /// <returns>The list with the country data.</returns>
        public List<string> GetCountries(int index)
        {
            Init();
            List<string> data = new List<string>();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT * FROM land WHERE landid = " + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                data.Add(reader.GetString(0));
                data.Add(reader.GetString(1));
            }
            conn.Close();
            return data;
        }

        /// <summary>
        /// Get the ID of a town based on the town's name
        /// </summary>
        /// <param name="name">The name of the town in question</param>
        /// <returns>The town ID</returns>
        public int GetCityID(string name)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedid FROM sted WHERE stedsnavn='" + name + "'";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Get the ID of a city based on the application ID
        /// </summary>
        /// <param name="index">The ID of the application in question.</param>
        /// <returns>The town ID</returns>
        public int GetCityID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedid FROM view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the name of a city based on the qunique city ID.
        /// </summary>
        /// <param name="index">The index of the city in question</param>
        /// <returns>The name of the city as a string.</returns>
        public string getCityName(int index)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedsnavn FROM STED where stedid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            conn.Close();
            return res;
        }

        /// <summary>
        /// Get the names of all registered cities.
        /// </summary>
        /// <returns>A list containing all registered cities</returns>
        public List<string> getCityNames()
        {
            List<string> res = new List<string>();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedsnavn FROM sted ORDER BY stedsnavn ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetString(0));
            return res;
        }

        /// <summary>
        /// Gets the names of all existing statuses.
        /// </summary>
        /// <returns>A list with all statuses</returns>
        public List<string> getStatusNames()
        {
            List<string> res = new List<string>();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT status FROM status ORDER BY status ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetString(0));
            return res;
        }

        /// <summary>
        /// Gets the country ID of a given application.
        /// </summary>
        /// <param name="index">The ID of the application in question.</param>
        /// <returns>The ID of the country.</returns>
        public int GetApplicationCountryID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        public int getCountryID(int cityid)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM sted WHERE stedid=" + cityid;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the ID of a country based on its name
        /// </summary>
        /// <param name="name">The name of the country in question</param>
        /// <returns>The country's ID</returns>
        public int getCountryID(string name)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM land WHERE land='" + name + "'";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }
        /// <summary>
        /// Builds an array list of all existing application IDs.
        /// </summary>
        /// <returns>An array list of existing application IDs</returns>
        public ArrayList GetApplicationIDs()
        {
            ArrayList res = new ArrayList();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT soknadid FROM soknad ORDER BY soknadid ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetInt32(0));
            return res;
        }

        /// <summary>
        /// Builds an array list of all existing country IDs.
        /// </summary>
        /// <returns>An array list of existing coutry IDs</returns>
        public ArrayList GetCountryIDs()
        {
            ArrayList res = new ArrayList();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM land ORDER BY landid ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetInt32(0));
            return res;
        }

        /// <summary>
        /// Builds an array list of all existing status IDs.
        /// </summary>
        /// <returns>An array list of existing status IDs</returns>
        public ArrayList GetStatusIDs()
        {
            ArrayList res = new ArrayList();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT statusid FROM status ORDER BY statusid ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetInt32(0));
            return res;
        }

        /// <summary>
        /// Builds an array list of all existing town IDs.
        /// </summary>
        /// <returns>An array list of existing town IDs</returns>
        public ArrayList GetTownIDs()
        {
            ArrayList res = new ArrayList();
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT stedid FROM sted ORDER BY stedid ASC";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res.Add(reader.GetInt32(0));
            return res;
        }

        /// <summary>
        /// Gets the ID of the country from the view "sted" (=town/place) based on the town ID.
        /// </summary>
        /// <param name="index">The ID of the town in question.</param>
        /// <returns>A number with the ID of the country.</returns>
        public int GetCityCountryID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM view_sted WHERE stedid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the ID of the country from the view "sted" (=town/place) based on the town name.
        /// </summary>
        /// <param name="index">The ID of the town in question.</param>
        /// <returns>A number with the ID of the country.</returns>
        public int GetCityCountryID(string townName)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT landid FROM view_sted WHERE stedsnavn='" + townName +"'";
            reader = cmd.ExecuteReader();
            while (reader.Read())
                ans = reader.GetInt32(0);
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the name of a country based on the provided ID.
        /// </summary>
        /// <param name="index">The ID of the country.</param>
        /// <returns>A string with the name of the country</returns>
        public string GetCountryName(int index)
        {
            string res = "";
            try
            {
                Init();
                cmd = new NpgsqlCommand("SELECT land FROM land WHERE landid=" + index + ";", conn);
                reader = cmd.ExecuteReader();
                while (reader.Read())
    res = reader.GetString(0);
                return res;
            }
            catch (NpgsqlException ne)
            {
                setError(ne.Message);
                return null;
            }
            finally
            {
                conn.Close();
            }
        }

        /// <summary>
        /// Gets the status ID of the provided status
        /// </summary>
        /// <param name="statusname">The name of the status in question</param>
        /// <returns>The ID of the provided status</returns>
        public int GetStatusID(string statusname)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT statusID from status WHERE status='" + statusname + "'";
            reader = cmd.ExecuteReader();
            while(reader.Read())
            {
                ans = reader.GetInt32(0);
            }
            conn.Close();
            return ans;
        }

        /// <summary>
        /// Gets the status ID based on the given parameter
        /// </summary>
        /// <param name="index">The application ID where the required status ID exists.</param>
        /// <returns>The required status ID.</returns>
        public int GetStatusID(int index)
        {
            int ans = 0;
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT statusID from view_soknad WHERE soknadid=" + index;
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                ans = reader.GetInt32(0);
            }
            conn.Close();
            return ans;
        }

        public string getMotivation(int idx)
        {
            try
            {
                string res = "";
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "SELECT motivasjon from view_soknad WHERE soknadid=" + idx;
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    res = reader.GetString(0);
                }
                conn.Close();
                return res;
            }
            catch(Exception)
            {
                conn.Close();
                return "";
            }
        }

        /// <summary>
        /// Gets the name of a status based on the parameter provided by the user.
        /// </summary>
        /// <param name="idx">The ID of the status in question.</param>
        /// <returns>A string containing the status name.</returns>
        public string getStatusName(int idx)
        {
            string res = "";
            Init();
            cmd = new NpgsqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = "SELECT status FROM status WHERE statusid=" + idx;
            reader = cmd.ExecuteReader();
            while (reader.Read())
                res = reader.GetString(0);
            conn.Close();
            return res;
        }
        
        /// <summary>
        /// Updates an existing job application.
        /// </summary>
        /// <param name="appID">The ID of the job application to be updated.</param>
        /// <param name="newAppTitle">The new application title.</param>
        /// <param name="newCompany">The new company name.</param>
        /// <param name="newTownID">The new ID of the town where the job is located.</param>
        /// <param name="newStatusID">The new status ID. 1=Registered, 2=Sent, 3=Interested, possible interview, 4=Declined/Rejected, 5=Application written but not sent, 6=Job accepted.</param>
        /// <param name="newDeadline">The new application deadline.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateApplication(int appID, string newAppTitle, string newCompany, int newTownID, int newStatusID, string newDeadline, string newMotivation)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE soknad SET tittel='" + newAppTitle + "', bedrift='" +newCompany + "', stedID=" + newTownID + ", statusID=" + newStatusID + ", soknadsfrist='" + newDeadline + "', motivasjon='" + newMotivation + "' where soknadid=" + appID + ";";
                cmd.ExecuteNonQuery();
                
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates an element in the table country
        /// </summary>
        /// <param name="countryID">The ID of the country to be updated.</param>
        /// <param name="newCountryName">The new name of the country.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateCountry(int countryID, string newCountryName)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE land SET land='" + newCountryName + "' where landid=" + countryID + ";";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates an existing status in the database.
        /// </summary>
        /// <param name="statusID">The unique identification number of the status to be updated</param>
        /// <param name="newStatusName">The new status name.</param>
        /// <returns>True on success and false on failure.</returns>
        public bool updateStatus(int statusID, string newStatusName)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE status SET status='" + newStatusName + "' where statusid=" + statusID + ";";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Updates a town that already exists in the database.
        /// </summary>
        /// <param name="oldTownName">The old name of the town to be updated.</param>
        /// <param name="newTownName">The new name of the town/city.</param>
        /// <returns></returns>
        public bool updateTown(string oldTownName, string newTownName, int newCountryID)
        {
            try
            {
                Init();
                cmd.Connection = conn;
                cmd.CommandText = "UPDATE sted SET stedsnavn='" + newTownName + "', landid=" +newCountryID + " where stedsnavn='" + oldTownName + "';";
                cmd.ExecuteNonQuery();
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                setError(noipe.Message);
                conn.Close();
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke oppdatere elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke oppdatere elementet. Feilmelding: " + e.Message);
                return false;
            }
            finally
            {
                conn.Close();
            }
            return true;
        }

        /// <summary>
        /// Deletes an item from the database
        /// </summary>
        /// <param name="table">The table where the item is located</param>
        /// <param name="columnName">The name of the column where the item to be deleted is located</param>
        /// <param name="index">The index (number) of the item to be deleted.</param>
        public bool DeleteItem(string table, string columnName, int index)
        {
            try
            {
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "DELETE FROM " + table + " WHERE " + columnName + " = " + index;
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (NpgsqlOperationInProgressException noipe)
            {
                //MessageBox.Show("Kan ikke fjerne elementet: " + noipe.ToString(), title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                setError(noipe.Message);
                return false;
            }
            catch (SocketException se)
            {
                setError("Kan ikke koble til serveren. Feilmelding: " + se.Message);
                return false;
            }
            catch (TimeoutException te)
            {
                setError("Kan ikke fjerne elementet. Det tok for lang tid å etablere forbindelse med serveren. Feilmelding: " + te.Message);
                return false;
            }
            catch (NpgsqlException ne)
            {
                setError("Kan ikke fjerne elementet. Feilmelding: " + ne.Message);
                return false;
            }
            catch (Exception e)
            {
                setError("Kan ikke fjerne elementet. Feilmelding: " + e.Message);
                return false;
            }

            finally
            {
                conn.Close();
            }
        }

        public List<string> GetData(string sqlQuery, int index)
        {
            Init();
            cmd = new NpgsqlCommand();
            try
            {
                data = new List<string>();
                cmd.Connection = conn;
                cmd.CommandText = sqlQuery;
                using (var rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        data.Add(rdr.GetString(index));
                    }
                }
                return data;
            }
            catch (NpgsqlOperationInProgressException)
            {
                Thread.Sleep(1000);
                GetData(sqlQuery, index);
                return null;
            }
            catch(Npgsql.NpgsqlException npe)
            {
                setError(npe.Message);
                throw npe;
            }

            finally
            {
                conn.Close();
            }
        }

        /*
         * Følgende kode er hentet fra QT-utgaven av samme program.
         * Funksjonen under brukes til å generere data om spesifikke søknader.
         * Koden i QT-utgaven brukes til å generere én kolonne per metode, men her bygges hele lista opp i én metode.
         */
        
        public List<jobb> getSpecificJobs(string jobTitle, string companyName, string cityName, string status, string deadline, string motivation)
        {
            List<jobb> data = new List<jobb>();
            try
            {
                Init();
                cmd = new NpgsqlCommand();
                cmd.Connection = conn;
                int i = 0;
                string s = "SELECT soknadid, tittel, bedrift, stedsnavn, status, soknadsfrist, motivasjon FROM view_soknad WHERE tittel like '%" + jobTitle + "%' and bedrift like '%" + companyName + "%' ";
                if (string.Compare(cityName, "", false) != 0)
    s = s + "and stedsnavn like '%" + cityName + "%' ";
                if (string.Compare(status, "", false) != 0)
    s = s + "and status like '%" + status + "%' ";
                s = s + "and soknadsfrist like '%" + deadline + "%' ";
                s = s + "and motivasjon like '%" + motivation + "%' order by soknadid;";
                cmd.CommandText = s;
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
    data.Add(new jobb() { applicationID = reader.GetInt32(0), jobTitle = reader.GetString(1), company = reader.GetString(2), cityName = reader.GetString(3), statusName = reader.GetString(4), deadline = reader.GetString(5), motivasjon = reader.GetString(6) });
    i++;
                }
                setRecord(i);
                conn.Close();
                return data;
            }
            catch(TimeoutException te)
            {
                throw te;
            }
            catch(SocketException se)
            {
                throw se;
            }
            catch(NpgsqlException ne)
            {
                throw ne;
            }
            catch(Exception e)
            {
                throw e; // Kaster bare feilen videre.
            }
        }
    }
}

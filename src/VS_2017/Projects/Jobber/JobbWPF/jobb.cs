using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JobbWPF
{
    // For å kunne fylle min dataGrid på en enkel måte, oppretter jeg en egen klasse kalt jobb som inneholder heltall og strenger
    // for søknadid, tittel, bedrift, stedsnavn, status, søknadsfrist og motivasjon.
    class jobb
    {
        public int applicationID { get; set; }
        public string jobTitle { get; set; }
        public string company { get; set; }
        public string cityName { get; set; }
        public string statusName { get; set; }
        public string deadline { get; set; }
        public string motivasjon { get; set; }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Vidly.dtos
{
    public class NewRentalDto
    {
        public int customerId { get; set; }
        public List<int> movieIds { get; set; }
    }
}
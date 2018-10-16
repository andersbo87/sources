using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using Vidly.dtos;
using Vidly.Models;

namespace Vidly.Controllers.api
{
    public class RentalsController : ApiController
    {
        ApplicationDbContext _context;
        public RentalsController()
        {
            _context = new ApplicationDbContext();
        }

        // Kode som tar seg av registrering av ny filmleie
        [HttpPost]
        public IHttpActionResult CreateRental(NewRentalDto newRental)
        {
            // Henter IDen til kunden som vil leie filmen(e).
            Customer customer = _context.customers.Single(c => c.id == newRental.customerId);

            // Bygger opp ei liste over filmer som kunden vil leie
            List<Movie> movies = _context.movies.Where(m => newRental.movieIds.Contains(m.id)).ToList();

            // Gjennomgår hver enkelt film
            foreach(Movie movie in movies)
            {
                // Hvis det ikke er flere filmer på lager:
                if (movie.numberAvailable == 0)
                    return BadRequest("Vi har ikke flere eksemplarer av denne filmen for øyeblikket.");

                // Oppdaterer antall tilgjengelige kopier ved å trekke 1 fra det opprinnelige tallet.
                movie.numberAvailable--;

                // Lager et nytt leieobjekt som assosierer kopien med kunden, filmen og tidspunkt for leia.
                Rental rental = new Rental
                {
                    customer = customer,
                    movie = movie,
                    dateRented = DateTime.Now
                };

                // Legger til i systemet
                _context.Rentals.Add(rental);
            }

            // Lagrer endringene
            _context.SaveChanges();
            return Ok();
        }
    }
}

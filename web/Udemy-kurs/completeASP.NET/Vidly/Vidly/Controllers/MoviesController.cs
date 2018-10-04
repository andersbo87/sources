using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using Vidly.Models;
using Vidly.Models.ViewModels;
using System.Data.Entity;
using System.Data.Entity.Validation;
using System;

namespace Vidly.Controllers
{
    public class MoviesController : Controller
    {
        private ApplicationDbContext _context;
        public MoviesController()
        {
            _context = new ApplicationDbContext();
        }

        protected override void Dispose(bool disposing)
        {
            _context.Dispose();
        }
        public ViewResult Index()
        {
            var movies = _context.movies.Include(m => m.genre).ToList();
            return View(movies);
        }

        public ActionResult Details(int id)
        {
            var movie = _context.movies.Include(m => m.genre).SingleOrDefault(m => m.id == id);
            if (movie == null)
                return HttpNotFound();

            return View(movie);
        }

        public IEnumerable<Movie> GetMovies()
        {
            return new List<Movie>
            {
                new Movie { id = 1, name = "Frost"},
                new Movie { id = 1, name = "Løvenes konge"}
            };
        }

        public ActionResult New()
        {
            List<Genre> genres = _context.genres.ToList();
            Movie movie = new Movie { releaseDate = DateTime.Now };
            MovieFormViewModel viewModel = new MovieFormViewModel
            {
                genres = genres
            };
            return View("MovieForm", viewModel);
        }

        // Følgende funksjon skal kun aktiveres via en POST request:
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Save(Movie movie)
        {
            if (!ModelState.IsValid)
            {
                var viewModel = new MovieFormViewModel(movie)
                {
                    genres = _context.genres.ToList()
                };

                return View("MovieForm", viewModel);
            }
            if (movie.id == 0)
            {
                movie.dateAdded = System.DateTime.Now;
                _context.movies.Add(movie);
            }
            else
            {
                Movie existingMovie = _context.movies.Single(m => m.id == movie.id);
                existingMovie.name = movie.name;
                existingMovie.genreId = movie.genreId;
                existingMovie.releaseDate = movie.releaseDate;
                existingMovie.numberInStock = movie.numberInStock;
            }

            try
            {
                _context.SaveChanges();
            }
            catch(DbEntityValidationException e)
            {
                System.Console.WriteLine(e);
            }
            return RedirectToAction("Index", "Movies");
        }

        public ActionResult Edit(int id)
        {
            Movie movie = _context.movies.SingleOrDefault(c => c.id == id);
            if (movie == null)
                return HttpNotFound();

            MovieFormViewModel viewModel = new MovieFormViewModel(movie)
            {
                movie = movie,
                genres = _context.genres.ToList()
            };

            return View("MovieForm", viewModel);
        }

        // GET: Movies
        /*public ActionResult Random()
        {
            Movie movie = new Movie() { name = "Frost" };

            List<Customer> customers = new List<Customer>
            {
                new Customer { name = "Kunde 1"},
                new Customer { name = "Kunde 2"}
            };

            RandomMovieViewModel viewModel = new RandomMovieViewModel
            {
                Movie = movie,
                Customers = customers
            };
            return View(viewModel);
        }

        [Route("movies/released/{year:regex(\\d{4})}/{month:regex(\\d{2}):range(1, 12)}")]
        public ActionResult ByReleaseDate(int year, byte month)
        {
            return Content(year + "/" + month);
        }

        public ActionResult Edit(int id)
        {
            return Content("id=" + id);
        }

        public ActionResult Index()
        {
            Movie movie = new Movie() { name = "Frost" };
            RandomMovieViewModel viewModel = new RandomMovieViewModel
            {
                Movie = movie,
                //Customers = customers
            };
            return View(viewModel); ;
        }*/

        /*public ActionResult Index(int? pageIndex, string sortBy)
        {
            if (!pageIndex.HasValue)
                pageIndex = 1;
            if (String.IsNullOrWhiteSpace(sortBy))
                sortBy = "Name";
            return Content(string.Format("pageIndex={0}&sortBy={1}", pageIndex, sortBy));

        }*/
    }
        }
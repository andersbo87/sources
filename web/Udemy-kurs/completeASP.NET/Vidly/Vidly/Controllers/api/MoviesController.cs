using AutoMapper;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using Vidly.dtos;
using Vidly.Models;

namespace Vidly.Controllers.api
{
    
    public class MoviesController : ApiController
    {
        private ApplicationDbContext _context;
        public MoviesController()
        {
            _context = new ApplicationDbContext();
        }

        // GET /movies
        public IEnumerable<MovieDto> GetMovies(string query = null)
        {
            /*return _context.movies
                .Include(m => m.genreType)
                .ToList()
                .Select(Mapper.Map<Movie, MovieDto>);*/

            var moviesQuery = _context.movies
                .Include(m => m.genreType)
                .Where(m => m.numberAvailable > 0);

            if (!String.IsNullOrWhiteSpace(query))
                moviesQuery = moviesQuery.Where(m => m.name.Contains(query));

            return moviesQuery.ToList().Select(Mapper.Map<Movie, MovieDto>);
        }

        // GET /movies/:id
        public IHttpActionResult GetMovie(int id)
        {
            Movie movie = _context.movies.SingleOrDefault(m => m.id == id);
            if (movie == null)
                return NotFound();

            return Ok(Mapper.Map<Movie, MovieDto>(movie));
        }

        // POST /movies
        [HttpPost]
        [Authorize(Roles = RoleName.canManageMovies)]
        public IHttpActionResult CreateMovie(MovieDto movieDto)
        {
            if (!ModelState.IsValid)
                return BadRequest();

            Movie movie = Mapper.Map<MovieDto, Movie>(movieDto);
            _context.movies.Add(movie);
            _context.SaveChanges();
            movie.id = movie.id;
            return Created(new Uri(Request.RequestUri + "/" + movie.id), movieDto);
        }

        // PUT /movies
        [HttpPut]
        [Authorize(Roles = RoleName.canManageMovies)]
        public IHttpActionResult UpdateMovie(int id, MovieDto movieDto)
        {
            if (!ModelState.IsValid)
                return NotFound();

            Movie existingMovie = _context.movies.SingleOrDefault(m => m.id == id);

            if (existingMovie == null)
                return NotFound();

            Mapper.Map(movieDto, existingMovie);

            return Ok();
        }

        // DELETE /movies
        [HttpDelete]
        [Authorize(Roles = RoleName.canManageMovies)]
        public IHttpActionResult DeleteMovie(int id)
        {
            Movie existingMovie = _context.movies.SingleOrDefault(m => m.id == id);
            if (existingMovie == null)
                return NotFound();

            _context.movies.Remove(existingMovie);
            _context.SaveChanges();
            return Ok();
        }
    }
}

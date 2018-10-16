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
    public class CustomersController : ApiController
    {
        private ApplicationDbContext _context;
        public CustomersController()
        {
            _context = new ApplicationDbContext();
        }
        // GET /api/customers
        public IHttpActionResult GetCustomers(string query = null)
        {
            var customerQuery = _context.customers
                .Include(c => c.membershipType);

            if (!String.IsNullOrWhiteSpace(query))
                customerQuery = customerQuery.Where(c => c.name.Contains(query));

            var customerDtos = customerQuery
                .ToList()
                .Select(Mapper.Map<Customer, CustomerDto>);
            return Ok(customerDtos);
        }

        // GET /api/customers/:id, e.g. /api/customers/1
        public IHttpActionResult GetCustomer(int id)
        {
            Customer customer = _context.customers.SingleOrDefault(c => c.id == id);
            if(customer == null)
            {
                return NotFound();
            }
            return Ok(Mapper.Map<Customer, CustomerDto>(customer));
        }

        // POST /api/customers
        [HttpPost]
        public IHttpActionResult CreateCustomer(CustomerDto customerDto)
        {
            if(!ModelState.IsValid)
            {
                return BadRequest();
            }

            Customer customer = Mapper.Map<CustomerDto, Customer>(customerDto);

            _context.customers.Add(customer);
            _context.SaveChanges();
            customerDto.id = customer.id;
            return Created(new Uri(Request.RequestUri + "/" + customer.id), customerDto);
        }

        // PUT /api/customers/:id
        [HttpPut]
        public IHttpActionResult UpdateCustomer(int id, CustomerDto customerDTO)
        {
            if (!ModelState.IsValid)
                return BadRequest();

            Customer existingCustomer = _context.customers.SingleOrDefault(c => c.id == id);
            if (existingCustomer == null)
                return NotFound();

            Mapper.Map(customerDTO, existingCustomer);

            _context.SaveChanges();
            return Ok();
        }

        // DELETE /api/customers/:id
        [HttpDelete]
        public IHttpActionResult DeleteCustomer(int id)
        {
            Customer existingCustomer = _context.customers.SingleOrDefault(c => c.id == id);
            if (existingCustomer == null)
                return NotFound();

            _context.customers.Remove(existingCustomer);
            _context.SaveChanges();
            return Ok();
        }
    }
}

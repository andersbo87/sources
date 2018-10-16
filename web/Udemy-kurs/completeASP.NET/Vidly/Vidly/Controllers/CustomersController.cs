using System;
using System.Collections;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Vidly.Models;
using Vidly.Models.ViewModels;

namespace Vidly.Controllers
{
    public class CustomersController : Controller
    {
        // GET: Customer
        private ApplicationDbContext _context;
        public CustomersController()
        {
            _context = new ApplicationDbContext();
        }

        protected override void Dispose(bool disposing)
        {
            _context.Dispose();
        }

        public ActionResult New()
        {
            List<MembershipType> membershipTypes = _context.membershipTypes.ToList();
            CustomerFormViewModel viewModel = new CustomerFormViewModel
            {
                customer = new Customer(),
                membershipTypes = membershipTypes
            };
            return View("CustomerForm", viewModel);
            // return View();

        }

        [HttpPost] // Forteller metoden at den bare skal ta seg av "POST requests".
        [ValidateAntiForgeryToken] // Se til at det ikke er noen hackere som står bak evt. angrep.
        public ActionResult Save(Customer customer)
        {
            if(!ModelState.IsValid)
            {
                CustomerFormViewModel viewModel = new CustomerFormViewModel
                {
                    customer = customer,
                    membershipTypes = _context.membershipTypes.ToList()
                };
                return View("CustomerForm", viewModel);
            }
            if (customer.id == 0)
            {
                _context.customers.Add(customer);
            }
            else
            {
                Customer existingCustomer = _context.customers.Single(c => c.id == customer.id);
                existingCustomer.name = customer.name;
                existingCustomer.birthday = customer.birthday;
                existingCustomer.membershipType = customer.membershipType;
                existingCustomer.isSubscribedToNewsletter = customer.isSubscribedToNewsletter;
            }
            _context.SaveChanges();
            return RedirectToAction("Index", "Customers");
        }

        public ViewResult Index()
        {
            //List<Customer> customers = _context.customers.Include(c => c.membershipType).ToList();
            if (User.IsInRole(RoleName.canManageMovies))
                return View("List");

            return View("ReadOnlyList");
            //return View();
        }
        public ActionResult Details(int id)
        {
            Customer customer = _context.customers.Include(c => c.membershipType).SingleOrDefault(c => c.id == id);
            if (customer == null)
                return HttpNotFound();
            return View(customer);
        }

        public ActionResult Edit(int id)
        {
            Customer customer = _context.customers.SingleOrDefault(c => c.id == id);
            if (customer == null)
                return HttpNotFound();

            CustomerFormViewModel viewModel = new CustomerFormViewModel
            {
                customer = customer,
                membershipTypes = _context.membershipTypes.ToList()
            };

            return View("CustomerForm", viewModel);
        }
    }
}
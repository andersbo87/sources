namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class insertGenres : DbMigration
    {
        public override void Up()
        {
            Sql("INSERT INTO GenreTypes (id, genreName) VALUES (1, 'Action')");
            Sql("INSERT INTO GenreTypes (id, genreName) VALUES (2, 'Thriller')");
            Sql("INSERT INTO GenreTypes (id, genreName) VALUES (3, 'Family')");
            Sql("INSERT INTO GenreTypes (id, genreName) VALUES (4, 'Romance')");
            Sql("INSERT INTO GenreTypes (id, genreName) VALUES (5, 'Comedy')");
        }
        
        public override void Down()
        {
        }
    }
}

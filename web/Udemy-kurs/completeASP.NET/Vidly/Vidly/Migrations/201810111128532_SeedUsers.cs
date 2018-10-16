namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class SeedUsers : DbMigration
    {
        public override void Up()
        {
            Sql(@"INSERT INTO [dbo].[AspNetUsers] ([Id], [Email], [EmailConfirmed], [PasswordHash], [SecurityStamp], [PhoneNumber], [PhoneNumberConfirmed], [TwoFactorEnabled], [LockoutEndDateUtc], [LockoutEnabled], [AccessFailedCount], [UserName]) VALUES (N'578ed912-33a1-4d3e-ad72-b8f4ce9fe0ff', N'guest@vidly.com', 0, N'AJ8+eH2kvL143t6AkMf7YLG+ujW1d4xCu7wLhbsxEDijcIm1VRcsb9rs7iBG9ti11A==', N'09a1036b-a483-4e39-9617-8b05e3c5b930', NULL, 0, 0, NULL, 1, 0, N'guest@vidly.com')
                  INSERT INTO[dbo].[AspNetUsers]([Id], [Email], [EmailConfirmed], [PasswordHash], [SecurityStamp], [PhoneNumber], [PhoneNumberConfirmed], [TwoFactorEnabled], [LockoutEndDateUtc], [LockoutEnabled], [AccessFailedCount], [UserName]) VALUES(N'f4be1c02-66b0-46f7-83fa-c90749fb72dc', N'admin@vidly.com', 0, N'AOhoUD70tyNXbIEZ75z6NZaYU425T2etEfoyYgRq9bd4hUjzVX9/9MgpnWP5PMoxNQ==', N'27f9723c-2ca4-4712-a140-03e8b9b5beff', NULL, 0, 0, NULL, 1, 0, N'admin@vidly.com')
                  INSERT INTO [dbo].[AspNetRoles] ([Id], [Name]) VALUES (N'da410d22-56eb-444d-833a-74f93de96314', N'CanManageMovies')
                  INSERT INTO [dbo].[AspNetUserRoles] ([UserId], [RoleId]) VALUES (N'f4be1c02-66b0-46f7-83fa-c90749fb72dc', N'da410d22-56eb-444d-833a-74f93de96314')
                ");
        }
        
        public override void Down()
        {
        }
    }
}

class InitialMigration < ActiveRecord::Migration
  def self.up

    create_table :users do |t|
      t.string :username
      t.string :password
    end

    create_table :blockeds do |t|
      t.integer :user_id
      t.string :ip
      t.string :port
    end

    create_table :protocols do |t|
      t.integer :blocked_id
      t.string :name
    end

    create_table :solo_protocols do |t|
      t.integer :protocol
    end
  end

  def self.down
    drop_table :blockeds
    drop_table :users
    drop_table :protocols
    drop_table :solo_protocols
  end
end


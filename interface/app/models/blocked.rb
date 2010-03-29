class Blocked < ActiveRecord::Base
  has_many :protocols, :dependent => :destroy
  belongs_to :users
end
class DashboardController < ApplicationController
def index
	render :overview
end

def overview
  render :overview
end

def ip
  render :ip
end

def protocols
  render :protocols
end

def rate
  render :rate
end

end 
